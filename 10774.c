static void addrconf_sit_config(struct net_device *dev)
{
	struct inet6_dev *idev;

	ASSERT_RTNL();

	/*
	 * Configure the tunnel with one of our IPv4
	 * addresses... we should configure all of
	 * our v4 addrs in the tunnel
	 */

	idev = ipv6_find_idev(dev);
	if (idev == NULL) {
		pr_debug("%s: add_dev failed\n", __func__);
		return;
	}

	if (dev->priv_flags & IFF_ISATAP) {
		addrconf_addr_gen(idev, false);
		return;
	}

	sit_add_v4_addrs(idev);

	if (dev->flags&IFF_POINTOPOINT)
		addrconf_add_mroute(dev);
}
