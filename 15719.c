static struct rtable *__mkroute_output(const struct fib_result *res,
				       const struct flowi4 *fl4, int orig_oif,
				       struct net_device *dev_out,
				       unsigned int flags)
{
	struct fib_info *fi = res->fi;
	struct fib_nh_exception *fnhe;
	struct in_device *in_dev;
	u16 type = res->type;
	struct rtable *rth;
	bool do_cache;

	in_dev = __in_dev_get_rcu(dev_out);
	if (!in_dev)
		return ERR_PTR(-EINVAL);

	if (likely(!IN_DEV_ROUTE_LOCALNET(in_dev)))
		if (ipv4_is_loopback(fl4->saddr) && !(dev_out->flags & IFF_LOOPBACK))
			return ERR_PTR(-EINVAL);

	if (ipv4_is_lbcast(fl4->daddr))
		type = RTN_BROADCAST;
	else if (ipv4_is_multicast(fl4->daddr))
		type = RTN_MULTICAST;
	else if (ipv4_is_zeronet(fl4->daddr))
		return ERR_PTR(-EINVAL);

	if (dev_out->flags & IFF_LOOPBACK)
		flags |= RTCF_LOCAL;

	do_cache = true;
	if (type == RTN_BROADCAST) {
		flags |= RTCF_BROADCAST | RTCF_LOCAL;
		fi = NULL;
	} else if (type == RTN_MULTICAST) {
		flags |= RTCF_MULTICAST | RTCF_LOCAL;
		if (!ip_check_mc_rcu(in_dev, fl4->daddr, fl4->saddr,
				     fl4->flowi4_proto))
			flags &= ~RTCF_LOCAL;
		else
			do_cache = false;
		/* If multicast route do not exist use
		 * default one, but do not gateway in this case.
		 * Yes, it is hack.
		 */
		if (fi && res->prefixlen < 4)
			fi = NULL;
	} else if ((type == RTN_LOCAL) && (orig_oif != 0) &&
		   (orig_oif != dev_out->ifindex)) {
		/* For local routes that require a particular output interface
		 * we do not want to cache the result.  Caching the result
		 * causes incorrect behaviour when there are multiple source
		 * addresses on the interface, the end result being that if the
		 * intended recipient is waiting on that interface for the
		 * packet he won't receive it because it will be delivered on
		 * the loopback interface and the IP_PKTINFO ipi_ifindex will
		 * be set to the loopback interface as well.
		 */
		fi = NULL;
	}

	fnhe = NULL;
	do_cache &= fi != NULL;
	if (do_cache) {
		struct rtable __rcu **prth;
		struct fib_nh *nh = &FIB_RES_NH(*res);

		fnhe = find_exception(nh, fl4->daddr);
		if (fnhe)
			prth = &fnhe->fnhe_rth_output;
		else {
			if (unlikely(fl4->flowi4_flags &
				     FLOWI_FLAG_KNOWN_NH &&
				     !(nh->nh_gw &&
				       nh->nh_scope == RT_SCOPE_LINK))) {
				do_cache = false;
				goto add;
			}
			prth = raw_cpu_ptr(nh->nh_pcpu_rth_output);
		}
		rth = rcu_dereference(*prth);
		if (rt_cache_valid(rth)) {
			dst_hold(&rth->dst);
			return rth;
		}
	}

add:
	rth = rt_dst_alloc(dev_out,
			   IN_DEV_CONF_GET(in_dev, NOPOLICY),
			   IN_DEV_CONF_GET(in_dev, NOXFRM),
			   do_cache);
	if (!rth)
		return ERR_PTR(-ENOBUFS);

	rth->dst.output = ip_output;

	rth->rt_genid = rt_genid_ipv4(dev_net(dev_out));
	rth->rt_flags	= flags;
	rth->rt_type	= type;
	rth->rt_is_input = 0;
	rth->rt_iif	= orig_oif ? : 0;
	rth->rt_pmtu	= 0;
	rth->rt_gateway = 0;
	rth->rt_uses_gateway = 0;
	INIT_LIST_HEAD(&rth->rt_uncached);

	RT_CACHE_STAT_INC(out_slow_tot);

	if (flags & RTCF_LOCAL)
		rth->dst.input = ip_local_deliver;
	if (flags & (RTCF_BROADCAST | RTCF_MULTICAST)) {
		if (flags & RTCF_LOCAL &&
		    !(dev_out->flags & IFF_LOOPBACK)) {
			rth->dst.output = ip_mc_output;
			RT_CACHE_STAT_INC(out_slow_mc);
		}
#ifdef CONFIG_IP_MROUTE
		if (type == RTN_MULTICAST) {
			if (IN_DEV_MFORWARD(in_dev) &&
			    !ipv4_is_local_multicast(fl4->daddr)) {
				rth->dst.input = ip_mr_input;
				rth->dst.output = ip_mc_output;
			}
		}
#endif
	}

	rt_set_nexthop(rth, fl4->daddr, res, fnhe, fi, type, 0);

	return rth;
}
