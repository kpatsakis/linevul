ip6_tnl_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	struct net_device_stats *stats = &t->dev->stats;
	int ret;

	switch (skb->protocol) {
	case htons(ETH_P_IP):
		ret = ip4ip6_tnl_xmit(skb, dev);
		break;
	case htons(ETH_P_IPV6):
		ret = ip6ip6_tnl_xmit(skb, dev);
		break;
	default:
		goto tx_err;
	}

	if (ret < 0)
		goto tx_err;

	return NETDEV_TX_OK;

tx_err:
	stats->tx_errors++;
	stats->tx_dropped++;
	kfree_skb(skb);
	return NETDEV_TX_OK;
}
