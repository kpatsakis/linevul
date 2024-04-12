static inline int ip6_forward_finish(struct sk_buff *skb)
{
	return dst_output(skb);
}
