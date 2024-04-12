mem_cgroup_get_local_stat(struct mem_cgroup *memcg, struct mcs_total_stat *s)
{
	s64 val;

	/* per cpu stat */
	val = mem_cgroup_read_stat(memcg, MEM_CGROUP_STAT_CACHE);
	s->stat[MCS_CACHE] += val * PAGE_SIZE;
	val = mem_cgroup_read_stat(memcg, MEM_CGROUP_STAT_RSS);
	s->stat[MCS_RSS] += val * PAGE_SIZE;
	val = mem_cgroup_read_stat(memcg, MEM_CGROUP_STAT_FILE_MAPPED);
	s->stat[MCS_FILE_MAPPED] += val * PAGE_SIZE;
	val = mem_cgroup_read_events(memcg, MEM_CGROUP_EVENTS_PGPGIN);
	s->stat[MCS_PGPGIN] += val;
	val = mem_cgroup_read_events(memcg, MEM_CGROUP_EVENTS_PGPGOUT);
	s->stat[MCS_PGPGOUT] += val;
	if (do_swap_account) {
		val = mem_cgroup_read_stat(memcg, MEM_CGROUP_STAT_SWAPOUT);
		s->stat[MCS_SWAP] += val * PAGE_SIZE;
	}
	val = mem_cgroup_read_events(memcg, MEM_CGROUP_EVENTS_PGFAULT);
	s->stat[MCS_PGFAULT] += val;
	val = mem_cgroup_read_events(memcg, MEM_CGROUP_EVENTS_PGMAJFAULT);
	s->stat[MCS_PGMAJFAULT] += val;

	/* per zone stat */
	val = mem_cgroup_nr_lru_pages(memcg, BIT(LRU_INACTIVE_ANON));
	s->stat[MCS_INACTIVE_ANON] += val * PAGE_SIZE;
	val = mem_cgroup_nr_lru_pages(memcg, BIT(LRU_ACTIVE_ANON));
	s->stat[MCS_ACTIVE_ANON] += val * PAGE_SIZE;
	val = mem_cgroup_nr_lru_pages(memcg, BIT(LRU_INACTIVE_FILE));
	s->stat[MCS_INACTIVE_FILE] += val * PAGE_SIZE;
	val = mem_cgroup_nr_lru_pages(memcg, BIT(LRU_ACTIVE_FILE));
	s->stat[MCS_ACTIVE_FILE] += val * PAGE_SIZE;
	val = mem_cgroup_nr_lru_pages(memcg, BIT(LRU_UNEVICTABLE));
	s->stat[MCS_UNEVICTABLE] += val * PAGE_SIZE;
}
