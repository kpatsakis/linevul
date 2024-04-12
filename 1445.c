static inline int rt_bandwidth_enabled(void)
{
	return sysctl_sched_rt_runtime >= 0;
}
