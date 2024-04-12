int dev_close(struct net_device *dev)
{
	if (!(dev->flags & IFF_UP))
		return 0;

	__dev_close(dev);

	/*
	 * Tell people we are down
	 */
	rtmsg_ifinfo(RTM_NEWLINK, dev, IFF_UP|IFF_RUNNING);
	call_netdevice_notifiers(NETDEV_DOWN, dev);

	return 0;
}
