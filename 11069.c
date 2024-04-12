static inline int armv8pmu_has_overflowed(u32 pmovsr)
{
	return pmovsr & ARMV8_OVERFLOWED_MASK;
}
