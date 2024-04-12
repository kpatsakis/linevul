static void perf_stop_nmi_watchdog(void *unused)
{
	struct cpu_hw_events *cpuc = &__get_cpu_var(cpu_hw_events);

	stop_nmi_watchdog(NULL);
	cpuc->pcr = pcr_ops->read();
}
