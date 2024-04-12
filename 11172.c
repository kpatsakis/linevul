static int mif6_delete(struct mr6_table *mrt, int vifi, struct list_head *head)
{
	struct mif_device *v;
	struct net_device *dev;
	struct inet6_dev *in6_dev;

	if (vifi < 0 || vifi >= mrt->maxvif)
		return -EADDRNOTAVAIL;

	v = &mrt->vif6_table[vifi];

	write_lock_bh(&mrt_lock);
	dev = v->dev;
	v->dev = NULL;

	if (!dev) {
		write_unlock_bh(&mrt_lock);
		return -EADDRNOTAVAIL;
	}

#ifdef CONFIG_IPV6_PIMSM_V2
	if (vifi == mrt->mroute_reg_vif_num)
		mrt->mroute_reg_vif_num = -1;
#endif

	if (vifi + 1 == mrt->maxvif) {
		int tmp;
		for (tmp = vifi - 1; tmp >= 0; tmp--) {
			if (MIF_EXISTS(mrt, tmp))
				break;
		}
		mrt->maxvif = tmp + 1;
	}

	write_unlock_bh(&mrt_lock);

	dev_set_allmulti(dev, -1);

	in6_dev = __in6_dev_get(dev);
	if (in6_dev) {
		in6_dev->cnf.mc_forwarding--;
		inet6_netconf_notify_devconf(dev_net(dev),
					     NETCONFA_MC_FORWARDING,
					     dev->ifindex, &in6_dev->cnf);
	}

	if (v->flags & MIFF_REGISTER)
		unregister_netdevice_queue(dev, head);

	dev_put(dev);
	return 0;
}
