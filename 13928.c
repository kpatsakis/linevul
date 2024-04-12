__mem_cgroup_uncharge_common(struct page *page, enum charge_type ctype)
{
	struct mem_cgroup *memcg = NULL;
	unsigned int nr_pages = 1;
	struct page_cgroup *pc;

	if (mem_cgroup_disabled())
		return NULL;

	if (PageSwapCache(page))
		return NULL;

	if (PageTransHuge(page)) {
		nr_pages <<= compound_order(page);
		VM_BUG_ON(!PageTransHuge(page));
	}
	/*
	 * Check if our page_cgroup is valid
	 */
	pc = lookup_page_cgroup(page);
	if (unlikely(!PageCgroupUsed(pc)))
		return NULL;

	lock_page_cgroup(pc);

	memcg = pc->mem_cgroup;

	if (!PageCgroupUsed(pc))
		goto unlock_out;

	switch (ctype) {
	case MEM_CGROUP_CHARGE_TYPE_MAPPED:
	case MEM_CGROUP_CHARGE_TYPE_DROP:
		/* See mem_cgroup_prepare_migration() */
		if (page_mapped(page) || PageCgroupMigration(pc))
			goto unlock_out;
		break;
	case MEM_CGROUP_CHARGE_TYPE_SWAPOUT:
		if (!PageAnon(page)) {	/* Shared memory */
			if (page->mapping && !page_is_file_cache(page))
				goto unlock_out;
		} else if (page_mapped(page)) /* Anon */
				goto unlock_out;
		break;
	default:
		break;
	}

	mem_cgroup_charge_statistics(memcg, PageCgroupCache(pc), -nr_pages);

	ClearPageCgroupUsed(pc);
	/*
	 * pc->mem_cgroup is not cleared here. It will be accessed when it's
	 * freed from LRU. This is safe because uncharged page is expected not
	 * to be reused (freed soon). Exception is SwapCache, it's handled by
	 * special functions.
	 */

	unlock_page_cgroup(pc);
	/*
	 * even after unlock, we have memcg->res.usage here and this memcg
	 * will never be freed.
	 */
	memcg_check_events(memcg, page);
	if (do_swap_account && ctype == MEM_CGROUP_CHARGE_TYPE_SWAPOUT) {
		mem_cgroup_swap_statistics(memcg, true);
		mem_cgroup_get(memcg);
	}
	if (!mem_cgroup_is_root(memcg))
		mem_cgroup_do_uncharge(memcg, nr_pages, ctype);

	return memcg;

unlock_out:
	unlock_page_cgroup(pc);
	return NULL;
}
