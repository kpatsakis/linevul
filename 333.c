static int pegasus_ioctl(struct net_device *net, struct ifreq *rq, int cmd)
{
	__u16 *data = (__u16 *) &rq->ifr_ifru;
	pegasus_t *pegasus = netdev_priv(net);
	int res;

	switch (cmd) {
	case SIOCDEVPRIVATE:
		data[0] = pegasus->phy;
	case SIOCDEVPRIVATE + 1:
		read_mii_word(pegasus, data[0], data[1] & 0x1f, &data[3]);
		res = 0;
		break;
	case SIOCDEVPRIVATE + 2:
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		write_mii_word(pegasus, pegasus->phy, data[1] & 0x1f, &data[2]);
		res = 0;
		break;
	default:
		res = -EOPNOTSUPP;
	}
	return res;
}
