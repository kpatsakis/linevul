static struct multipath *alloc_multipath(struct dm_target *ti)
{
	struct multipath *m;

	m = kzalloc(sizeof(*m), GFP_KERNEL);
	if (m) {
		INIT_LIST_HEAD(&m->priority_groups);
		INIT_LIST_HEAD(&m->queued_ios);
		spin_lock_init(&m->lock);
		m->queue_io = 1;
		m->pg_init_delay_msecs = DM_PG_INIT_DELAY_DEFAULT;
		INIT_WORK(&m->process_queued_ios, process_queued_ios);
		INIT_WORK(&m->trigger_event, trigger_event);
		init_waitqueue_head(&m->pg_init_wait);
		mutex_init(&m->work_mutex);
		m->mpio_pool = mempool_create_slab_pool(MIN_IOS, _mpio_cache);
		if (!m->mpio_pool) {
			kfree(m);
			return NULL;
		}
		m->ti = ti;
		ti->private = m;
	}

	return m;
}
