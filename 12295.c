bool mem_cgroup_reclaimable(struct mem_cgroup *memcg, bool noswap)
{
	return test_mem_cgroup_node_reclaimable(memcg, 0, noswap);
}
