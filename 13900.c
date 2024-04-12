static inline u32 armv7_pmnc_enable_counter(unsigned int idx)
{
	u32 val;

	if ((idx != ARMV7_CYCLE_COUNTER) &&
	    ((idx < ARMV7_COUNTER0) || (idx > ARMV7_COUNTER_LAST))) {
		pr_err("CPU%u enabling wrong PMNC counter"
			" %d\n", smp_processor_id(), idx);
		return -1;
	}

	if (idx == ARMV7_CYCLE_COUNTER)
		val = ARMV7_CNTENS_C;
	else
		val = ARMV7_CNTENS_P(idx);

	asm volatile("mcr p15, 0, %0, c9, c12, 1" : : "r" (val));

	return idx;
}
