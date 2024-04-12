static void dev_unicast_init(struct net_device *dev)
{
	__hw_addr_init(&dev->uc);
}
