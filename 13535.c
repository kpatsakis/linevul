static int rt_bind_neighbour(struct rtable *rt)
{
	struct neighbour *n = ipv4_neigh_lookup(&rt->dst, &rt->rt_gateway);
	if (IS_ERR(n))
		return PTR_ERR(n);
	dst_set_neighbour(&rt->dst, n);

	return 0;
}
