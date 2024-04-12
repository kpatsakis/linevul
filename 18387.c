static int __init ifb_init_one(int index)
{
	struct net_device *dev_ifb;
	int err;

	dev_ifb = alloc_netdev(sizeof(struct ifb_private),
				 "ifb%d", ifb_setup);

	if (!dev_ifb)
		return -ENOMEM;

	dev_ifb->rtnl_link_ops = &ifb_link_ops;
	err = register_netdevice(dev_ifb);
	if (err < 0)
		goto err;

	return 0;

err:
	free_netdev(dev_ifb);
	return err;
}
