u32 ip_mtu_from_fib_result(struct fib_result *res, __be32 daddr)
{
	struct fib_info *fi = res->fi;
	struct fib_nh *nh = &fi->fib_nh[res->nh_sel];
	struct net_device *dev = nh->nh_dev;
	u32 mtu = 0;

	if (dev_net(dev)->ipv4.sysctl_ip_fwd_use_pmtu ||
	    fi->fib_metrics->metrics[RTAX_LOCK - 1] & (1 << RTAX_MTU))
		mtu = fi->fib_mtu;

	if (likely(!mtu)) {
		struct fib_nh_exception *fnhe;

		fnhe = find_exception(nh, daddr);
		if (fnhe && !time_after_eq(jiffies, fnhe->fnhe_expires))
			mtu = fnhe->fnhe_pmtu;
	}

	if (likely(!mtu))
		mtu = min(READ_ONCE(dev->mtu), IP_MAX_MTU);

	return mtu - lwtunnel_headroom(nh->nh_lwtstate, mtu);
}
