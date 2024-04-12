static int mem_cgroup_force_empty_list(struct mem_cgroup *memcg,
				int node, int zid, enum lru_list lru)
{
	struct mem_cgroup_per_zone *mz;
	unsigned long flags, loop;
	struct list_head *list;
	struct page *busy;
	struct zone *zone;
	int ret = 0;

	zone = &NODE_DATA(node)->node_zones[zid];
	mz = mem_cgroup_zoneinfo(memcg, node, zid);
	list = &mz->lruvec.lists[lru];

	loop = MEM_CGROUP_ZSTAT(mz, lru);
	/* give some margin against EBUSY etc...*/
	loop += 256;
	busy = NULL;
	while (loop--) {
		struct page_cgroup *pc;
		struct page *page;

		ret = 0;
		spin_lock_irqsave(&zone->lru_lock, flags);
		if (list_empty(list)) {
			spin_unlock_irqrestore(&zone->lru_lock, flags);
			break;
		}
		page = list_entry(list->prev, struct page, lru);
		if (busy == page) {
			list_move(&page->lru, list);
			busy = NULL;
			spin_unlock_irqrestore(&zone->lru_lock, flags);
			continue;
		}
		spin_unlock_irqrestore(&zone->lru_lock, flags);

		pc = lookup_page_cgroup(page);

		ret = mem_cgroup_move_parent(page, pc, memcg, GFP_KERNEL);
		if (ret == -ENOMEM || ret == -EINTR)
			break;

		if (ret == -EBUSY || ret == -EINVAL) {
			/* found lock contention or "pc" is obsolete. */
			busy = page;
			cond_resched();
		} else
			busy = NULL;
	}

	if (!ret && !list_empty(list))
		return -EBUSY;
	return ret;
}
