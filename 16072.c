ip6_tnl_dev_uninit(struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	struct net *net = dev_net(dev);
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	if (dev == ip6n->fb_tnl_dev) {
		spin_lock_bh(&ip6_tnl_lock);
		ip6n->tnls_wc[0] = NULL;
		spin_unlock_bh(&ip6_tnl_lock);
	} else {
		ip6_tnl_unlink(ip6n, t);
	}
	ip6_tnl_dst_reset(t);
	dev_put(dev);
}
