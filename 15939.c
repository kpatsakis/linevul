void llc_conn_resend_i_pdu_as_rsp(struct sock *sk, u8 nr, u8 first_f_bit)
{
	struct sk_buff *skb;
	u16 nbr_unack_pdus;
	struct llc_sock *llc = llc_sk(sk);
	u8 howmany_resend = 0;

	llc_conn_remove_acked_pdus(sk, nr, &nbr_unack_pdus);
	if (!nbr_unack_pdus)
		goto out;
	/*
	 * Process unack PDUs only if unack queue is not empty; remove
	 * appropriate PDUs, fix them up, and put them on mac_pdu_q
	 */
	while ((skb = skb_dequeue(&llc->pdu_unack_q)) != NULL) {
		struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

		llc_pdu_set_cmd_rsp(skb, LLC_PDU_RSP);
		llc_pdu_set_pf_bit(skb, first_f_bit);
		skb_queue_tail(&sk->sk_write_queue, skb);
		first_f_bit = 0;
		llc->vS = LLC_I_GET_NS(pdu);
		howmany_resend++;
	}
	if (howmany_resend > 0)
		llc->vS = (llc->vS + 1) % LLC_2_SEQ_NBR_MODULO;
	/* any PDUs to re-send are queued up; start sending to MAC */
	llc_conn_send_pdus(sk);
out:;
}
