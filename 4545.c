static void xen_netbk_rx_action(struct xen_netbk *netbk)
{
	struct xenvif *vif = NULL, *tmp;
	s8 status;
	u16 irq, flags;
	struct xen_netif_rx_response *resp;
	struct sk_buff_head rxq;
	struct sk_buff *skb;
	LIST_HEAD(notify);
	int ret;
	int nr_frags;
	int count;
	unsigned long offset;
	struct skb_cb_overlay *sco;

	struct netrx_pending_operations npo = {
		.copy  = netbk->grant_copy_op,
		.meta  = netbk->meta,
	};

	skb_queue_head_init(&rxq);

	count = 0;

	while ((skb = skb_dequeue(&netbk->rx_queue)) != NULL) {
		vif = netdev_priv(skb->dev);
		nr_frags = skb_shinfo(skb)->nr_frags;

		sco = (struct skb_cb_overlay *)skb->cb;
		sco->meta_slots_used = netbk_gop_skb(skb, &npo);

		count += nr_frags + 1;

		__skb_queue_tail(&rxq, skb);

		/* Filled the batch queue? */
		if (count + MAX_SKB_FRAGS >= XEN_NETIF_RX_RING_SIZE)
			break;
	}

	BUG_ON(npo.meta_prod > ARRAY_SIZE(netbk->meta));

	if (!npo.copy_prod)
		return;

	BUG_ON(npo.copy_prod > ARRAY_SIZE(netbk->grant_copy_op));
	gnttab_batch_copy(netbk->grant_copy_op, npo.copy_prod);

	while ((skb = __skb_dequeue(&rxq)) != NULL) {
		sco = (struct skb_cb_overlay *)skb->cb;

		vif = netdev_priv(skb->dev);

		if (netbk->meta[npo.meta_cons].gso_size && vif->gso_prefix) {
			resp = RING_GET_RESPONSE(&vif->rx,
						vif->rx.rsp_prod_pvt++);

			resp->flags = XEN_NETRXF_gso_prefix | XEN_NETRXF_more_data;

			resp->offset = netbk->meta[npo.meta_cons].gso_size;
			resp->id = netbk->meta[npo.meta_cons].id;
			resp->status = sco->meta_slots_used;

			npo.meta_cons++;
			sco->meta_slots_used--;
		}


		vif->dev->stats.tx_bytes += skb->len;
		vif->dev->stats.tx_packets++;

		status = netbk_check_gop(vif, sco->meta_slots_used, &npo);

		if (sco->meta_slots_used == 1)
			flags = 0;
		else
			flags = XEN_NETRXF_more_data;

		if (skb->ip_summed == CHECKSUM_PARTIAL) /* local packet? */
			flags |= XEN_NETRXF_csum_blank | XEN_NETRXF_data_validated;
		else if (skb->ip_summed == CHECKSUM_UNNECESSARY)
			/* remote but checksummed. */
			flags |= XEN_NETRXF_data_validated;

		offset = 0;
		resp = make_rx_response(vif, netbk->meta[npo.meta_cons].id,
					status, offset,
					netbk->meta[npo.meta_cons].size,
					flags);

		if (netbk->meta[npo.meta_cons].gso_size && !vif->gso_prefix) {
			struct xen_netif_extra_info *gso =
				(struct xen_netif_extra_info *)
				RING_GET_RESPONSE(&vif->rx,
						  vif->rx.rsp_prod_pvt++);

			resp->flags |= XEN_NETRXF_extra_info;

			gso->u.gso.size = netbk->meta[npo.meta_cons].gso_size;
			gso->u.gso.type = XEN_NETIF_GSO_TYPE_TCPV4;
			gso->u.gso.pad = 0;
			gso->u.gso.features = 0;

			gso->type = XEN_NETIF_EXTRA_TYPE_GSO;
			gso->flags = 0;
		}

		netbk_add_frag_responses(vif, status,
					 netbk->meta + npo.meta_cons + 1,
					 sco->meta_slots_used);

		RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&vif->rx, ret);
		irq = vif->irq;
		if (ret && list_empty(&vif->notify_list))
			list_add_tail(&vif->notify_list, &notify);

		xenvif_notify_tx_completion(vif);

		xenvif_put(vif);
		npo.meta_cons += sco->meta_slots_used;
		dev_kfree_skb(skb);
	}

	list_for_each_entry_safe(vif, tmp, &notify, notify_list) {
		notify_remote_via_irq(vif->irq);
		list_del_init(&vif->notify_list);
	}

	/* More work to do? */
	if (!skb_queue_empty(&netbk->rx_queue) &&
			!timer_pending(&netbk->net_timer))
		xen_netbk_kick_thread(netbk);
}
