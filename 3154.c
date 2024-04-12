static int mem_cgroup_force_empty(struct mem_cgroup *memcg, bool free_all)
{
	int ret;
	int node, zid, shrink;
	int nr_retries = MEM_CGROUP_RECLAIM_RETRIES;
	struct cgroup *cgrp = memcg->css.cgroup;

	css_get(&memcg->css);

	shrink = 0;
	/* should free all ? */
	if (free_all)
		goto try_to_free;
move_account:
	do {
		ret = -EBUSY;
		if (cgroup_task_count(cgrp) || !list_empty(&cgrp->children))
			goto out;
		ret = -EINTR;
		if (signal_pending(current))
			goto out;
		/* This is for making all *used* pages to be on LRU. */
		lru_add_drain_all();
		drain_all_stock_sync(memcg);
		ret = 0;
		mem_cgroup_start_move(memcg);
		for_each_node_state(node, N_HIGH_MEMORY) {
			for (zid = 0; !ret && zid < MAX_NR_ZONES; zid++) {
				enum lru_list l;
				for_each_lru(l) {
					ret = mem_cgroup_force_empty_list(memcg,
							node, zid, l);
					if (ret)
						break;
				}
			}
			if (ret)
				break;
		}
		mem_cgroup_end_move(memcg);
		memcg_oom_recover(memcg);
		/* it seems parent cgroup doesn't have enough mem */
		if (ret == -ENOMEM)
			goto try_to_free;
		cond_resched();
	/* "ret" should also be checked to ensure all lists are empty. */
	} while (memcg->res.usage > 0 || ret);
out:
	css_put(&memcg->css);
	return ret;

try_to_free:
	/* returns EBUSY if there is a task or if we come here twice. */
	if (cgroup_task_count(cgrp) || !list_empty(&cgrp->children) || shrink) {
		ret = -EBUSY;
		goto out;
	}
	/* we call try-to-free pages for make this cgroup empty */
	lru_add_drain_all();
	/* try to free all pages in this cgroup */
	shrink = 1;
	while (nr_retries && memcg->res.usage > 0) {
		int progress;

		if (signal_pending(current)) {
			ret = -EINTR;
			goto out;
		}
		progress = try_to_free_mem_cgroup_pages(memcg, GFP_KERNEL,
						false);
		if (!progress) {
			nr_retries--;
			/* maybe some writeback is necessary */
			congestion_wait(BLK_RW_ASYNC, HZ/10);
		}

	}
	lru_add_drain();
	/* try move_account...there may be some *locked* pages. */
	goto move_account;
}
