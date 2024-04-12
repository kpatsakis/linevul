 timeval_to_double(const timeval_t *t)
{
	/* The casts are necessary to avoid conversion warnings */
	return (double)t->tv_sec + (double)t->tv_usec / TIMER_HZ_FLOAT;
}
