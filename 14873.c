static void watchdog_enable_all_cpus(void)
{
	int cpu;

	watchdog_enabled = 0;

	for_each_online_cpu(cpu)
		if (!watchdog_enable(cpu))
			/* if any cpu succeeds, watchdog is considered
			   enabled for the system */
			watchdog_enabled = 1;

	if (!watchdog_enabled)
		printk(KERN_ERR "watchdog: failed to be enabled on some cpus\n");

}
