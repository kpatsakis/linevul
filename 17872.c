static int slab_offline_cpu(unsigned int cpu)
{
	/*
	 * Shutdown cache reaper. Note that the slab_mutex is held so
	 * that if cache_reap() is invoked it cannot do anything
	 * expensive but will only modify reap_work and reschedule the
	 * timer.
	 */
	cancel_delayed_work_sync(&per_cpu(slab_reap_work, cpu));
	/* Now the cache_reaper is guaranteed to be not running. */
	per_cpu(slab_reap_work, cpu).work.func = NULL;
	return 0;
}
