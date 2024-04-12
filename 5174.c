static int fwnet_open(struct net_device *net)
{
	struct fwnet_device *dev = netdev_priv(net);
	int ret;

	ret = fwnet_broadcast_start(dev);
	if (ret)
		return ret;

	netif_start_queue(net);

	spin_lock_irq(&dev->lock);
	set_carrier_state(dev);
	spin_unlock_irq(&dev->lock);

	return 0;
}
