cleanup_prefix_route(struct inet6_ifaddr *ifp, unsigned long expires, bool del_rt)
{
	struct rt6_info *rt;

	rt = addrconf_get_prefix_route(&ifp->addr,
				       ifp->prefix_len,
				       ifp->idev->dev,
				       0, RTF_GATEWAY | RTF_DEFAULT);
	if (rt) {
		if (del_rt)
			ip6_del_rt(rt);
		else {
			if (!(rt->rt6i_flags & RTF_EXPIRES))
				rt6_set_expires(rt, expires);
			ip6_rt_put(rt);
		}
	}
}
