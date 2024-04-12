armv6pmu_disable_event(struct hw_perf_event *hwc,
		       int idx)
{
	unsigned long val, mask, evt, flags;

	if (ARMV6_CYCLE_COUNTER == idx) {
		mask	= ARMV6_PMCR_CCOUNT_IEN;
		evt	= 0;
	} else if (ARMV6_COUNTER0 == idx) {
		mask	= ARMV6_PMCR_COUNT0_IEN | ARMV6_PMCR_EVT_COUNT0_MASK;
		evt	= ARMV6_PERFCTR_NOP << ARMV6_PMCR_EVT_COUNT0_SHIFT;
	} else if (ARMV6_COUNTER1 == idx) {
		mask	= ARMV6_PMCR_COUNT1_IEN | ARMV6_PMCR_EVT_COUNT1_MASK;
		evt	= ARMV6_PERFCTR_NOP << ARMV6_PMCR_EVT_COUNT1_SHIFT;
	} else {
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		return;
	}

	/*
	 * Mask out the current event and set the counter to count the number
	 * of ETM bus signal assertion cycles. The external reporting should
	 * be disabled and so this should never increment.
	 */
	raw_spin_lock_irqsave(&pmu_lock, flags);
	val = armv6_pmcr_read();
	val &= ~mask;
	val |= evt;
	armv6_pmcr_write(val);
	raw_spin_unlock_irqrestore(&pmu_lock, flags);
}
