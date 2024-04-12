static void mem_cgroup_swap_statistics(struct mem_cgroup *memcg,
					 bool charge)
{
	int val = (charge) ? 1 : -1;
	this_cpu_add(memcg->stat->count[MEM_CGROUP_STAT_SWAPOUT], val);
}
