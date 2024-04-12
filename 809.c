__be32 inet_current_timestamp(void)
{
	u32 secs;
	u32 msecs;
	struct timespec64 ts;

	ktime_get_real_ts64(&ts);

	/* Get secs since midnight. */
	(void)div_u64_rem(ts.tv_sec, SECONDS_PER_DAY, &secs);
	/* Convert to msecs. */
	msecs = secs * MSEC_PER_SEC;
	/* Convert nsec to msec. */
	msecs += (u32)ts.tv_nsec / NSEC_PER_MSEC;

	/* Convert to network byte order. */
	return htons(msecs);
}
