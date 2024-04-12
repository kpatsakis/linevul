record_timing_stats(
	const char *text	/* text message */
	)
{
	static unsigned int flshcnt;
	l_fp	now;
	u_long	day;

	if (!stats_control)
		return;

	get_systime(&now);
	filegen_setup(&timingstats, now.l_ui);
	day = now.l_ui / 86400 + MJD_1900;
	now.l_ui %= 86400;
	if (timingstats.fp != NULL) {
		fprintf(timingstats.fp, "%lu %s %s\n", day, lfptoa(&now,
		    3), text);
		if (++flshcnt % 100 == 0)
			fflush(timingstats.fp);
	}
}
