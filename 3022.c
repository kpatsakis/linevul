static void x86_pmu_start_txn(struct pmu *pmu)
{
	perf_pmu_disable(pmu);
	__this_cpu_or(cpu_hw_events.group_flag, PERF_EVENT_TXN);
	__this_cpu_write(cpu_hw_events.n_txn, 0);
}
