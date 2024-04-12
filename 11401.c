write_stats(void)
{
	FILE	*fp;
#ifdef DOSYNCTODR
	struct timeval tv;
#if !defined(VMS)
	int	prio_set;
#endif
#ifdef HAVE_GETCLOCK
	struct timespec ts;
#endif
	int	o_prio;

	/*
	 * Sometimes having a Sun can be a drag.
	 *
	 * The kernel variable dosynctodr controls whether the system's
	 * soft clock is kept in sync with the battery clock. If it
	 * is zero, then the soft clock is not synced, and the battery
	 * clock is simply left to rot. That means that when the system
	 * reboots, the battery clock (which has probably gone wacky)
	 * sets the soft clock. That means ntpd starts off with a very
	 * confused idea of what time it is. It then takes a large
	 * amount of time to figure out just how wacky the battery clock
	 * has made things drift, etc, etc. The solution is to make the
	 * battery clock sync up to system time. The way to do THAT is
	 * to simply set the time of day to the current time of day, but
	 * as quickly as possible. This may, or may not be a sensible
	 * thing to do.
	 *
	 * CAVEAT: settimeofday() steps the sun clock by about 800 us,
	 *	   so setting DOSYNCTODR seems a bad idea in the
	 *	   case of us resolution
	 */

#if !defined(VMS)
	/*
	 * (prr) getpriority returns -1 on error, but -1 is also a valid
	 * return value (!), so instead we have to zero errno before the
	 * call and check it for non-zero afterwards.
	 */
	errno = 0;
	prio_set = 0;
	o_prio = getpriority(PRIO_PROCESS,0); /* Save setting */

	/*
	 * (prr) if getpriority succeeded, call setpriority to raise
	 * scheduling priority as high as possible.  If that succeeds
	 * as well, set the prio_set flag so we remember to reset
	 * priority to its previous value below.  Note that on Solaris
	 * 2.6 (and beyond?), both getpriority and setpriority will fail
	 * with ESRCH, because sched_setscheduler (called from main) put
	 * us in the real-time scheduling class which setpriority
	 * doesn't know about. Being in the real-time class is better
	 * than anything setpriority can do, anyhow, so this error is
	 * silently ignored.
	 */
	if ((errno == 0) && (setpriority(PRIO_PROCESS,0,-20) == 0))
		prio_set = 1;	/* overdrive */
#endif /* VMS */
#ifdef HAVE_GETCLOCK
	(void) getclock(TIMEOFDAY, &ts);
	tv.tv_sec = ts.tv_sec;
	tv.tv_usec = ts.tv_nsec / 1000;
#else /*  not HAVE_GETCLOCK */
	GETTIMEOFDAY(&tv,(struct timezone *)NULL);
#endif /* not HAVE_GETCLOCK */
	if (ntp_set_tod(&tv,(struct timezone *)NULL) != 0)
		msyslog(LOG_ERR, "can't sync battery time: %m");
#if !defined(VMS)
	if (prio_set)
		setpriority(PRIO_PROCESS, 0, o_prio); /* downshift */
#endif /* VMS */
#endif /* DOSYNCTODR */
	record_sys_stats();
	if (stats_drift_file != 0) {

		/*
		 * When the frequency file is written, initialize the
		 * prev_drift_comp and wander_resid. Thereafter,
		 * reduce the wander_resid by half each hour. When
		 * the difference between the prev_drift_comp and
		 * drift_comp is less than the wander_resid, update
		 * the frequncy file. This minimizes the file writes to
		 * nonvolaile storage.
		 */
#ifdef DEBUG
		if (debug)
			printf("write_stats: frequency %.6lf thresh %.6lf, freq %.6lf\n",
			    (prev_drift_comp - drift_comp) * 1e6, wander_resid *
			    1e6, drift_comp * 1e6);
#endif
		if (fabs(prev_drift_comp - drift_comp) < wander_resid) {
			wander_resid *= 0.5;
			return;
		}
		prev_drift_comp = drift_comp;
		wander_resid = wander_threshold;
		if ((fp = fopen(stats_temp_file, "w")) == NULL) {
			msyslog(LOG_ERR, "frequency file %s: %m",
			    stats_temp_file);
			return;
		}
		fprintf(fp, "%.3f\n", drift_comp * 1e6);
		(void)fclose(fp);
		/* atomic */
#ifdef SYS_WINNT
		if (_unlink(stats_drift_file)) /* rename semantics differ under NT */
			msyslog(LOG_WARNING, 
				"Unable to remove prior drift file %s, %m", 
				stats_drift_file);
#endif /* SYS_WINNT */

#ifndef NO_RENAME
		if (rename(stats_temp_file, stats_drift_file))
			msyslog(LOG_WARNING, 
				"Unable to rename temp drift file %s to %s, %m", 
				stats_temp_file, stats_drift_file);
#else
		/* we have no rename NFS of ftp in use */
		if ((fp = fopen(stats_drift_file, "w")) ==
		    NULL) {
			msyslog(LOG_ERR,
			    "frequency file %s: %m",
			    stats_drift_file);
			return;
		}
#endif

#if defined(VMS)
		/* PURGE */
		{
			$DESCRIPTOR(oldvers,";-1");
			struct dsc$descriptor driftdsc = {
				strlen(stats_drift_file), 0, 0,
				    stats_drift_file };
			while(lib$delete_file(&oldvers,
			    &driftdsc) & 1);
		}
#endif
	}
}
