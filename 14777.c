static void release_pmc_hardware(void)
{
	int i;

	for (i = 0; i < x86_pmu.num_counters; i++) {
		release_perfctr_nmi(x86_pmu_event_addr(i));
		release_evntsel_nmi(x86_pmu_config_addr(i));
	}
}
