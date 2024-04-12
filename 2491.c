static inline u32 armv7pmu_read_counter(int idx)
{
	unsigned long value = 0;

	if (idx == ARMV7_CYCLE_COUNTER)
		asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r" (value));
	else if ((idx >= ARMV7_COUNTER0) && (idx <= ARMV7_COUNTER_LAST)) {
		if (armv7_pmnc_select_counter(idx) == idx)
			asm volatile("mrc p15, 0, %0, c9, c13, 2"
				     : "=r" (value));
	} else
		pr_err("CPU%u reading wrong counter %d\n",
			smp_processor_id(), idx);

	return value;
}
