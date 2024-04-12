static void dev_change_rx_flags(struct net_device *dev, int flags)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	if ((dev->flags & IFF_UP) && ops->ndo_change_rx_flags)
		ops->ndo_change_rx_flags(dev, flags);
}
