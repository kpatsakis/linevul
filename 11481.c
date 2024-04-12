static void free_skb_pool(rtl8150_t *dev)
{
	int i;

	for (i = 0; i < RX_SKB_POOL_SIZE; i++)
		if (dev->rx_skb_pool[i])
			dev_kfree_skb(dev->rx_skb_pool[i]);
}
