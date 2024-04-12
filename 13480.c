long get_timeval_diff(const GTimeVal *tv1, const GTimeVal *tv2)
{
	long secs, usecs;

	secs = tv1->tv_sec - tv2->tv_sec;
	usecs = tv1->tv_usec - tv2->tv_usec;
	if (usecs < 0) {
		usecs += 1000000;
		secs--;
	}
	usecs = usecs/1000 + secs * 1000;

	return usecs;
}
