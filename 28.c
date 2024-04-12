armv6_pmcr_has_overflowed(unsigned long pmcr)
{
	return pmcr & ARMV6_PMCR_OVERFLOWED_MASK;
}
