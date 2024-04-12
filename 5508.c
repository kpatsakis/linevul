cpu_callback(struct notifier_block *nfb, unsigned long action, void *hcpu)
{
	int hotcpu = (unsigned long)hcpu;

	switch (action) {
	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		watchdog_prepare_cpu(hotcpu);
		break;
	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		if (watchdog_enabled)
			watchdog_enable(hotcpu);
		break;
#ifdef CONFIG_HOTPLUG_CPU
	case CPU_UP_CANCELED:
	case CPU_UP_CANCELED_FROZEN:
		watchdog_disable(hotcpu);
		break;
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		watchdog_disable(hotcpu);
		break;
#endif /* CONFIG_HOTPLUG_CPU */
	}

	/*
	 * hardlockup and softlockup are not important enough
	 * to block cpu bring up.  Just always succeed and
	 * rely on printk output to flag problems.
	 */
	return NOTIFY_OK;
}
