static void mem_cgroup_start_move(struct mem_cgroup *memcg)
{
	int cpu;

	get_online_cpus();
	spin_lock(&memcg->pcp_counter_lock);
	for_each_online_cpu(cpu)
		per_cpu(memcg->stat->count[MEM_CGROUP_ON_MOVE], cpu) += 1;
	memcg->nocpu_base.count[MEM_CGROUP_ON_MOVE] += 1;
	spin_unlock(&memcg->pcp_counter_lock);
	put_online_cpus();

	synchronize_rcu();
}
