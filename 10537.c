void dccp_v4_send_check(struct sock *sk, struct sk_buff *skb)
{
	const struct inet_sock *inet = inet_sk(sk);
	struct dccp_hdr *dh = dccp_hdr(skb);

	dccp_csum_outgoing(skb);
	dh->dccph_checksum = dccp_v4_csum_finish(skb,
						 inet->inet_saddr,
						 inet->inet_daddr);
}
