static int is_hardlockup(void)
{
	unsigned long hrint = __this_cpu_read(hrtimer_interrupts);

	if (__this_cpu_read(hrtimer_interrupts_saved) == hrint)
		return 1;

	__this_cpu_write(hrtimer_interrupts_saved, hrint);
	return 0;
}
