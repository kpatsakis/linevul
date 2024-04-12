static struct rtable *__mkroute_output(const struct fib_result *res,
				       const struct flowi4 *fl4,
				       __be32 orig_daddr, __be32 orig_saddr,
				       int orig_oif, struct net_device *dev_out,
				       unsigned int flags)
{
	struct fib_info *fi = res->fi;
	u32 tos = RT_FL_TOS(fl4);
	struct in_device *in_dev;
	u16 type = res->type;
	struct rtable *rth;

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

	in_dev = __in_dev_get_rcu(dev_out);
	if (!in_dev)
		return ERR_PTR(-EINVAL);

	if (type == RTN_BROADCAST) {
		flags |= RTCF_BROADCAST | RTCF_LOCAL;
		fi = NULL;
	} else if (type == RTN_MULTICAST) {
		flags |= RTCF_MULTICAST | RTCF_LOCAL;
		if (!ip_check_mc_rcu(in_dev, fl4->daddr, fl4->saddr,
				     fl4->flowi4_proto))
			flags &= ~RTCF_LOCAL;
		/* If multicast route do not exist use
		 * default one, but do not gateway in this case.
		 * Yes, it is hack.
		 */
		if (fi && res->prefixlen < 4)
			fi = NULL;
	}

	rth = rt_dst_alloc(dev_out,
			   IN_DEV_CONF_GET(in_dev, NOPOLICY),
			   IN_DEV_CONF_GET(in_dev, NOXFRM));
	if (!rth)
		return ERR_PTR(-ENOBUFS);

	rth->dst.output = ip_output;

	rth->rt_key_dst	= orig_daddr;
	rth->rt_key_src	= orig_saddr;
	rth->rt_genid = rt_genid(dev_net(dev_out));
	rth->rt_flags	= flags;
	rth->rt_type	= type;
	rth->rt_key_tos	= tos;
	rth->rt_dst	= fl4->daddr;
	rth->rt_src	= fl4->saddr;
	rth->rt_route_iif = 0;
	rth->rt_iif	= orig_oif ? : dev_out->ifindex;
	rth->rt_oif	= orig_oif;
	rth->rt_mark    = fl4->flowi4_mark;
	rth->rt_gateway = fl4->daddr;
	rth->rt_spec_dst= fl4->saddr;
	rth->rt_peer_genid = 0;
	rth->peer = NULL;
	rth->fi = NULL;

	RT_CACHE_STAT_INC(out_slow_tot);

	if (flags & RTCF_LOCAL) {
		rth->dst.input = ip_local_deliver;
		rth->rt_spec_dst = fl4->daddr;
	}
	if (flags & (RTCF_BROADCAST | RTCF_MULTICAST)) {
		rth->rt_spec_dst = fl4->saddr;
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

	rt_set_nexthop(rth, fl4, res, fi, type, 0);

	return rth;
}
