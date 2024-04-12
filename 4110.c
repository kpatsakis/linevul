void perf_event_grab_pmc(void)
{
	if (atomic_inc_not_zero(&active_events))
		return;

	mutex_lock(&pmc_grab_mutex);
	if (atomic_read(&active_events) == 0) {
		if (atomic_read(&nmi_active) > 0) {
			on_each_cpu(perf_stop_nmi_watchdog, NULL, 1);
			BUG_ON(atomic_read(&nmi_active) != 0);
		}
		atomic_inc(&active_events);
	}
	mutex_unlock(&pmc_grab_mutex);
}
