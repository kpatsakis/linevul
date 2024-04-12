static bool numamigrate_update_ratelimit(pg_data_t *pgdat,
					unsigned long nr_pages)
{
	/*
	 * Rate-limit the amount of data that is being migrated to a node.
	 * Optimal placement is no good if the memory bus is saturated and
	 * all the time is being spent migrating!
	 */
	if (time_after(jiffies, pgdat->numabalancing_migrate_next_window)) {
		spin_lock(&pgdat->numabalancing_migrate_lock);
		pgdat->numabalancing_migrate_nr_pages = 0;
		pgdat->numabalancing_migrate_next_window = jiffies +
			msecs_to_jiffies(migrate_interval_millisecs);
		spin_unlock(&pgdat->numabalancing_migrate_lock);
	}
	if (pgdat->numabalancing_migrate_nr_pages > ratelimit_pages) {
		trace_mm_numa_migrate_ratelimit(current, pgdat->node_id,
								nr_pages);
		return true;
	}

	/*
	 * This is an unlocked non-atomic update so errors are possible.
	 * The consequences are failing to migrate when we potentiall should
	 * have which is not severe enough to warrant locking. If it is ever
	 * a problem, it can be converted to a per-cpu counter.
	 */
	pgdat->numabalancing_migrate_nr_pages += nr_pages;
	return false;
}
