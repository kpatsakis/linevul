static bool low_pfn(unsigned long pfn)
{
	return pfn < max_low_pfn;
}
