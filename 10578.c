static int dccp_v6_rcv(struct sk_buff *skb)
{
	const struct dccp_hdr *dh;
	struct sock *sk;
	int min_cov;

	/* Step 1: Check header basics */

	if (dccp_invalid_packet(skb))
		goto discard_it;

	/* Step 1: If header checksum is incorrect, drop packet and return. */
	if (dccp_v6_csum_finish(skb, &ipv6_hdr(skb)->saddr,
				     &ipv6_hdr(skb)->daddr)) {
		DCCP_WARN("dropped packet with invalid checksum\n");
		goto discard_it;
	}

	dh = dccp_hdr(skb);

	DCCP_SKB_CB(skb)->dccpd_seq  = dccp_hdr_seq(dh);
	DCCP_SKB_CB(skb)->dccpd_type = dh->dccph_type;

	if (dccp_packet_without_ack(skb))
		DCCP_SKB_CB(skb)->dccpd_ack_seq = DCCP_PKT_WITHOUT_ACK_SEQ;
	else
		DCCP_SKB_CB(skb)->dccpd_ack_seq = dccp_hdr_ack_seq(skb);

	/* Step 2:
	 *	Look up flow ID in table and get corresponding socket */
	sk = __inet6_lookup_skb(&dccp_hashinfo, skb,
			        dh->dccph_sport, dh->dccph_dport);
	/*
	 * Step 2:
	 *	If no socket ...
	 */
	if (sk == NULL) {
		dccp_pr_debug("failed to look up flow ID in table and "
			      "get corresponding socket\n");
		goto no_dccp_socket;
	}

	/*
	 * Step 2:
	 *	... or S.state == TIMEWAIT,
	 *		Generate Reset(No Connection) unless P.type == Reset
	 *		Drop packet and return
	 */
	if (sk->sk_state == DCCP_TIME_WAIT) {
		dccp_pr_debug("sk->sk_state == DCCP_TIME_WAIT: do_time_wait\n");
		inet_twsk_put(inet_twsk(sk));
		goto no_dccp_socket;
	}

	/*
	 * RFC 4340, sec. 9.2.1: Minimum Checksum Coverage
	 *	o if MinCsCov = 0, only packets with CsCov = 0 are accepted
	 *	o if MinCsCov > 0, also accept packets with CsCov >= MinCsCov
	 */
	min_cov = dccp_sk(sk)->dccps_pcrlen;
	if (dh->dccph_cscov  &&  (min_cov == 0 || dh->dccph_cscov < min_cov))  {
		dccp_pr_debug("Packet CsCov %d does not satisfy MinCsCov %d\n",
			      dh->dccph_cscov, min_cov);
		/* FIXME: send Data Dropped option (see also dccp_v4_rcv) */
		goto discard_and_relse;
	}

	if (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
		goto discard_and_relse;

	return sk_receive_skb(sk, skb, 1) ? -1 : 0;

no_dccp_socket:
	if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb))
		goto discard_it;
	/*
	 * Step 2:
	 *	If no socket ...
	 *		Generate Reset(No Connection) unless P.type == Reset
	 *		Drop packet and return
	 */
	if (dh->dccph_type != DCCP_PKT_RESET) {
		DCCP_SKB_CB(skb)->dccpd_reset_code =
					DCCP_RESET_CODE_NO_CONNECTION;
		dccp_v6_ctl_send_reset(sk, skb);
	}

discard_it:
	kfree_skb(skb);
	return 0;

discard_and_relse:
	sock_put(sk);
	goto discard_it;
}
