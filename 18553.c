static bool rt_cache_route(struct fib_nh *nh, struct rtable *rt)
{
	struct rtable *orig, *prev, **p;
	bool ret = true;

	if (rt_is_input_route(rt)) {
		p = (struct rtable **)&nh->nh_rth_input;
	} else {
		p = (struct rtable **)raw_cpu_ptr(nh->nh_pcpu_rth_output);
	}
	orig = *p;

	prev = cmpxchg(p, orig, rt);
	if (prev == orig) {
		if (orig)
			rt_free(orig);
	} else
		ret = false;

	return ret;
}
