static void send_mpa_req(struct iwch_ep *ep, struct sk_buff *skb)
{
	int mpalen;
	struct tx_data_wr *req;
	struct mpa_message *mpa;
	int len;

	PDBG("%s ep %p pd_len %d\n", __func__, ep, ep->plen);

	BUG_ON(skb_cloned(skb));

	mpalen = sizeof(*mpa) + ep->plen;
	if (skb->data + mpalen + sizeof(*req) > skb_end_pointer(skb)) {
		kfree_skb(skb);
		skb=alloc_skb(mpalen + sizeof(*req), GFP_KERNEL);
		if (!skb) {
			connect_reply_upcall(ep, -ENOMEM);
			return;
		}
	}
	skb_trim(skb, 0);
	skb_reserve(skb, sizeof(*req));
	skb_put(skb, mpalen);
	skb->priority = CPL_PRIORITY_DATA;
	mpa = (struct mpa_message *) skb->data;
	memset(mpa, 0, sizeof(*mpa));
	memcpy(mpa->key, MPA_KEY_REQ, sizeof(mpa->key));
	mpa->flags = (crc_enabled ? MPA_CRC : 0) |
		     (markers_enabled ? MPA_MARKERS : 0);
	mpa->private_data_size = htons(ep->plen);
	mpa->revision = mpa_rev;

	if (ep->plen)
		memcpy(mpa->private_data, ep->mpa_pkt + sizeof(*mpa), ep->plen);

	/*
	 * Reference the mpa skb.  This ensures the data area
	 * will remain in memory until the hw acks the tx.
	 * Function tx_ack() will deref it.
	 */
	skb_get(skb);
	set_arp_failure_handler(skb, arp_failure_discard);
	skb_reset_transport_header(skb);
	len = skb->len;
	req = (struct tx_data_wr *) skb_push(skb, sizeof(*req));
	req->wr_hi = htonl(V_WR_OP(FW_WROPCODE_OFLD_TX_DATA)|F_WR_COMPL);
	req->wr_lo = htonl(V_WR_TID(ep->hwtid));
	req->len = htonl(len);
	req->param = htonl(V_TX_PORT(ep->l2t->smt_idx) |
			   V_TX_SNDBUF(snd_win>>15));
	req->flags = htonl(F_TX_INIT);
	req->sndseq = htonl(ep->snd_seq);
	BUG_ON(ep->mpa_skb);
	ep->mpa_skb = skb;
	iwch_l2t_send(ep->com.tdev, skb, ep->l2t);
	start_ep_timer(ep);
	state_set(&ep->com, MPA_REQ_SENT);
	return;
}
