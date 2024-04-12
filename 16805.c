static int fwnet_stop(struct net_device *net)
{
	struct fwnet_device *dev = netdev_priv(net);

	netif_stop_queue(net);
	fwnet_broadcast_stop(dev);

	return 0;
}
