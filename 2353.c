static void receive_buf(struct virtnet_info *vi, struct receive_queue *rq,
			void *buf, unsigned int len)
{
	struct net_device *dev = vi->dev;
	struct virtnet_stats *stats = this_cpu_ptr(vi->stats);
	struct sk_buff *skb;
	struct virtio_net_hdr_mrg_rxbuf *hdr;

	if (unlikely(len < vi->hdr_len + ETH_HLEN)) {
		pr_debug("%s: short packet %i\n", dev->name, len);
		dev->stats.rx_length_errors++;
		if (vi->mergeable_rx_bufs) {
			unsigned long ctx = (unsigned long)buf;
			void *base = mergeable_ctx_to_buf_address(ctx);
			put_page(virt_to_head_page(base));
		} else if (vi->big_packets) {
			give_pages(rq, buf);
		} else {
			dev_kfree_skb(buf);
		}
		return;
	}

	if (vi->mergeable_rx_bufs)
		skb = receive_mergeable(dev, vi, rq, (unsigned long)buf, len);
	else if (vi->big_packets)
		skb = receive_big(dev, vi, rq, buf, len);
	else
		skb = receive_small(vi, buf, len);

	if (unlikely(!skb))
		return;

	hdr = skb_vnet_hdr(skb);

	u64_stats_update_begin(&stats->rx_syncp);
	stats->rx_bytes += skb->len;
	stats->rx_packets++;
	u64_stats_update_end(&stats->rx_syncp);

	if (hdr->hdr.flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) {
		pr_debug("Needs csum!\n");
		if (!skb_partial_csum_set(skb,
			  virtio16_to_cpu(vi->vdev, hdr->hdr.csum_start),
			  virtio16_to_cpu(vi->vdev, hdr->hdr.csum_offset)))
			goto frame_err;
	} else if (hdr->hdr.flags & VIRTIO_NET_HDR_F_DATA_VALID) {
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	}

	skb->protocol = eth_type_trans(skb, dev);
	pr_debug("Receiving skb proto 0x%04x len %i type %i\n",
		 ntohs(skb->protocol), skb->len, skb->pkt_type);

	if (hdr->hdr.gso_type != VIRTIO_NET_HDR_GSO_NONE) {
		pr_debug("GSO!\n");
		switch (hdr->hdr.gso_type & ~VIRTIO_NET_HDR_GSO_ECN) {
		case VIRTIO_NET_HDR_GSO_TCPV4:
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
			break;
		case VIRTIO_NET_HDR_GSO_UDP:
			skb_shinfo(skb)->gso_type = SKB_GSO_UDP;
			break;
		case VIRTIO_NET_HDR_GSO_TCPV6:
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
			break;
		default:
			net_warn_ratelimited("%s: bad gso type %u.\n",
					     dev->name, hdr->hdr.gso_type);
			goto frame_err;
		}

		if (hdr->hdr.gso_type & VIRTIO_NET_HDR_GSO_ECN)
			skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;

		skb_shinfo(skb)->gso_size = virtio16_to_cpu(vi->vdev,
							    hdr->hdr.gso_size);
		if (skb_shinfo(skb)->gso_size == 0) {
			net_warn_ratelimited("%s: zero gso size.\n", dev->name);
			goto frame_err;
		}

		/* Header must be checked, and gso_segs computed. */
		skb_shinfo(skb)->gso_type |= SKB_GSO_DODGY;
		skb_shinfo(skb)->gso_segs = 0;
	}

	skb_mark_napi_id(skb, &rq->napi);

	netif_receive_skb(skb);
	return;

frame_err:
	dev->stats.rx_frame_errors++;
	dev_kfree_skb(skb);
}
