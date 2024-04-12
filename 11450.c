static unsigned long get_sample_period(void)
{
	/*
	 * convert watchdog_thresh from seconds to ns
	 * the divide by 5 is to give hrtimer 5 chances to
	 * increment before the hardlockup detector generates
	 * a warning
	 */
	return get_softlockup_thresh() * (NSEC_PER_SEC / 5);
}
