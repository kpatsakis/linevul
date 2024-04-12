static int ipv4_sysctl_rtcache_flush(struct ctl_table *__ctl, int write,
					void __user *buffer,
					size_t *lenp, loff_t *ppos)
{
	struct net *net = (struct net *)__ctl->extra1;

	if (write) {
		rt_cache_flush(net);
		fnhe_genid_bump(net);
		return 0;
	}

	return -EINVAL;
}
