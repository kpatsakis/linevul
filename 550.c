static int mem_cgroup_move_account(struct page *page,
				   unsigned int nr_pages,
				   struct page_cgroup *pc,
				   struct mem_cgroup *from,
				   struct mem_cgroup *to,
				   bool uncharge)
{
	unsigned long flags;
	int ret;

	VM_BUG_ON(from == to);
	VM_BUG_ON(PageLRU(page));
	/*
	 * The page is isolated from LRU. So, collapse function
	 * will not handle this page. But page splitting can happen.
	 * Do this check under compound_page_lock(). The caller should
	 * hold it.
	 */
	ret = -EBUSY;
	if (nr_pages > 1 && !PageTransHuge(page))
		goto out;

	lock_page_cgroup(pc);

	ret = -EINVAL;
	if (!PageCgroupUsed(pc) || pc->mem_cgroup != from)
		goto unlock;

	move_lock_page_cgroup(pc, &flags);

	if (PageCgroupFileMapped(pc)) {
		/* Update mapped_file data for mem_cgroup */
		preempt_disable();
		__this_cpu_dec(from->stat->count[MEM_CGROUP_STAT_FILE_MAPPED]);
		__this_cpu_inc(to->stat->count[MEM_CGROUP_STAT_FILE_MAPPED]);
		preempt_enable();
	}
	mem_cgroup_charge_statistics(from, PageCgroupCache(pc), -nr_pages);
	if (uncharge)
		/* This is not "cancel", but cancel_charge does all we need. */
		__mem_cgroup_cancel_charge(from, nr_pages);

	/* caller should have done css_get */
	pc->mem_cgroup = to;
	mem_cgroup_charge_statistics(to, PageCgroupCache(pc), nr_pages);
	/*
	 * We charges against "to" which may not have any tasks. Then, "to"
	 * can be under rmdir(). But in current implementation, caller of
	 * this function is just force_empty() and move charge, so it's
	 * guaranteed that "to" is never removed. So, we don't check rmdir
	 * status here.
	 */
	move_unlock_page_cgroup(pc, &flags);
	ret = 0;
unlock:
	unlock_page_cgroup(pc);
	/*
	 * check events
	 */
	memcg_check_events(to, page);
	memcg_check_events(from, page);
out:
	return ret;
}
