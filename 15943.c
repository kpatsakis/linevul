static int get_callchain_buffers(void)
{
	int err = 0;
	int count;

	mutex_lock(&callchain_mutex);

	count = atomic_inc_return(&nr_callchain_events);
	if (WARN_ON_ONCE(count < 1)) {
		err = -EINVAL;
		goto exit;
	}

	if (count > 1) {
		/* If the allocation failed, give up */
		if (!callchain_cpus_entries)
			err = -ENOMEM;
		goto exit;
	}

	err = alloc_callchain_buffers();
	if (err)
		release_callchain_buffers();
exit:
	mutex_unlock(&callchain_mutex);

	return err;
}
