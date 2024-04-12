void net_disable_timestamp(void)
{
#ifdef HAVE_JUMP_LABEL
	if (in_interrupt()) {
		atomic_inc(&netstamp_needed_deferred);
		return;
	}
#endif
	static_key_slow_dec(&netstamp_needed);
}
