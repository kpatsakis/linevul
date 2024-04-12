struct blk_desc *blk_get_dev(const char *ifname, int dev)
{
	return get_dev_hwpart(ifname, dev, 0);
}
