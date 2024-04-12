static void ip_rt_build_flow_key(struct flowi4 *fl4, const struct sock *sk,
				 const struct sk_buff *skb)
{
	if (skb)
		build_skb_flow_key(fl4, skb, sk);
	else
		build_sk_flow_key(fl4, sk);
}
