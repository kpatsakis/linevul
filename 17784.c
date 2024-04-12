static bool test_mem_cgroup_node_reclaimable(struct mem_cgroup *memcg,
		int nid, bool noswap)
{
	if (mem_cgroup_node_nr_lru_pages(memcg, nid, LRU_ALL_FILE))
		return true;
	if (noswap || !total_swap_pages)
		return false;
	if (mem_cgroup_node_nr_lru_pages(memcg, nid, LRU_ALL_ANON))
		return true;
	return false;

}
