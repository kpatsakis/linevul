static void perf_pmu_cancel_txn(struct pmu *pmu)
{
	perf_pmu_enable(pmu);
}
