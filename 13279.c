static void dispatch_queued_ios(struct multipath *m)
{
	int r;
	unsigned long flags;
	struct dm_mpath_io *mpio;
	union map_info *info;
	struct request *clone, *n;
	LIST_HEAD(cl);

	spin_lock_irqsave(&m->lock, flags);
	list_splice_init(&m->queued_ios, &cl);
	spin_unlock_irqrestore(&m->lock, flags);

	list_for_each_entry_safe(clone, n, &cl, queuelist) {
		list_del_init(&clone->queuelist);

		info = dm_get_rq_mapinfo(clone);
		mpio = info->ptr;

		r = map_io(m, clone, mpio, 1);
		if (r < 0) {
			mempool_free(mpio, m->mpio_pool);
			dm_kill_unmapped_request(clone, r);
		} else if (r == DM_MAPIO_REMAPPED)
			dm_dispatch_request(clone);
		else if (r == DM_MAPIO_REQUEUE) {
			mempool_free(mpio, m->mpio_pool);
			dm_requeue_unmapped_request(clone);
		}
	}
}
