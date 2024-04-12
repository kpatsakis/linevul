xscale2pmu_read_event_select(void)
{
	u32 val;
	asm volatile("mrc p14, 0, %0, c8, c1, 0" : "=r" (val));
	return val;
}
