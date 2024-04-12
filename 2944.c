static int rtl8150_close(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);

	netif_stop_queue(netdev);
	if (!test_bit(RTL8150_UNPLUG, &dev->flags))
		disable_net_traffic(dev);
	unlink_all_urbs(dev);

	return 0;
}
