int netif_receive_skb(struct sk_buff *skb)
{
	trace_netif_receive_skb_entry(skb);

	return netif_receive_skb_internal(skb);
}
