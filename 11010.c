static int tcp_disordered_ack(const struct sock *sk, const struct sk_buff *skb)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct tcphdr *th = tcp_hdr(skb);
	u32 seq = TCP_SKB_CB(skb)->seq;
	u32 ack = TCP_SKB_CB(skb)->ack_seq;

	return (/* 1. Pure ACK with correct sequence number. */
		(th->ack && seq == TCP_SKB_CB(skb)->end_seq && seq == tp->rcv_nxt) &&

		/* 2. ... and duplicate ACK. */
		ack == tp->snd_una &&

		/* 3. ... and does not update window. */
		!tcp_may_update_window(tp, ack, seq, ntohs(th->window) << tp->rx_opt.snd_wscale) &&

		/* 4. ... and sits in replay window. */
		(s32)(tp->rx_opt.ts_recent - tp->rx_opt.rcv_tsval) <= (inet_csk(sk)->icsk_rto * 1024) / HZ);
}
