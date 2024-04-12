static void perf_cpu_hrtimer_restart(struct perf_cpu_context *cpuctx)
{
	struct hrtimer *hr = &cpuctx->hrtimer;
	struct pmu *pmu = cpuctx->ctx.pmu;

	/* not for SW PMU */
	if (pmu->task_ctx_nr == perf_sw_context)
		return;

	if (hrtimer_active(hr))
		return;

	if (!hrtimer_callback_running(hr))
		__hrtimer_start_range_ns(hr, cpuctx->hrtimer_interval,
					 0, HRTIMER_MODE_REL_PINNED, 0);
}
