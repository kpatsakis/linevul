static void fill_skb_pool(rtl8150_t *dev)
{
	struct sk_buff *skb;
	int i;

	for (i = 0; i < RX_SKB_POOL_SIZE; i++) {
		if (dev->rx_skb_pool[i])
			continue;
		skb = dev_alloc_skb(RTL8150_MTU + 2);
		if (!skb) {
			return;
		}
		skb_reserve(skb, 2);
		dev->rx_skb_pool[i] = skb;
	}
}
