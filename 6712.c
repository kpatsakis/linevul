static int posix_get_boottime(const clockid_t which_clock, struct timespec64 *tp)
{
	ktime_get_boottime_ts64(tp);
	return 0;
}
