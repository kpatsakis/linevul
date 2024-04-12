static inline struct sk_buff *pull_skb(rtl8150_t *dev)
{
	struct sk_buff *skb;
	int i;

	for (i = 0; i < RX_SKB_POOL_SIZE; i++) {
		if (dev->rx_skb_pool[i]) {
			skb = dev->rx_skb_pool[i];
			dev->rx_skb_pool[i] = NULL;
			return skb;
		}
	}
	return NULL;
}
