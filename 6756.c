static void armv7pmu_reset(void *info)
{
	u32 idx, nb_cnt = armpmu->num_events;

	/* The counter and interrupt enable registers are unknown at reset. */
	for (idx = 1; idx < nb_cnt; ++idx)
		armv7pmu_disable_event(NULL, idx);

	/* Initialize & Reset PMNC: C and P bits */
	armv7_pmnc_write(ARMV7_PMNC_P | ARMV7_PMNC_C);
}
