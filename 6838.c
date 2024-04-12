struct dst_entry *ipv4_blackhole_route(struct net *net, struct dst_entry *dst_orig)
{
	struct rtable *rt = dst_alloc(&ipv4_dst_blackhole_ops, NULL, 1, 0, 0);
	struct rtable *ort = (struct rtable *) dst_orig;

	if (rt) {
		struct dst_entry *new = &rt->dst;

		new->__use = 1;
		new->input = dst_discard;
		new->output = dst_discard;
		dst_copy_metrics(new, &ort->dst);

		new->dev = ort->dst.dev;
		if (new->dev)
			dev_hold(new->dev);

		rt->rt_key_dst = ort->rt_key_dst;
		rt->rt_key_src = ort->rt_key_src;
		rt->rt_key_tos = ort->rt_key_tos;
		rt->rt_route_iif = ort->rt_route_iif;
		rt->rt_iif = ort->rt_iif;
		rt->rt_oif = ort->rt_oif;
		rt->rt_mark = ort->rt_mark;

		rt->rt_genid = rt_genid(net);
		rt->rt_flags = ort->rt_flags;
		rt->rt_type = ort->rt_type;
		rt->rt_dst = ort->rt_dst;
		rt->rt_src = ort->rt_src;
		rt->rt_gateway = ort->rt_gateway;
		rt->rt_spec_dst = ort->rt_spec_dst;
		rt->peer = ort->peer;
		if (rt->peer)
			atomic_inc(&rt->peer->refcnt);
		rt->fi = ort->fi;
		if (rt->fi)
			atomic_inc(&rt->fi->fib_clntref);

		dst_free(new);
	}

	dst_release(dst_orig);

	return rt ? &rt->dst : ERR_PTR(-ENOMEM);
}
