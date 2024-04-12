int mem_cgroup_cache_charge(struct page *page, struct mm_struct *mm,
				gfp_t gfp_mask)
{
	struct mem_cgroup *memcg = NULL;
	enum charge_type type = MEM_CGROUP_CHARGE_TYPE_CACHE;
	int ret;

	if (mem_cgroup_disabled())
		return 0;
	if (PageCompound(page))
		return 0;

	if (unlikely(!mm))
		mm = &init_mm;
	if (!page_is_file_cache(page))
		type = MEM_CGROUP_CHARGE_TYPE_SHMEM;

	if (!PageSwapCache(page))
		ret = mem_cgroup_charge_common(page, mm, gfp_mask, type);
	else { /* page is swapcache/shmem */
		ret = mem_cgroup_try_charge_swapin(mm, page, gfp_mask, &memcg);
		if (!ret)
			__mem_cgroup_commit_charge_swapin(page, memcg, type);
	}
	return ret;
}
