void perf_sched_cb_dec(struct pmu *pmu)
{
	this_cpu_dec(perf_sched_cb_usages);
}
