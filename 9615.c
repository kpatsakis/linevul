static void free_rootdomain(struct rcu_head *rcu)
{
	struct root_domain *rd = container_of(rcu, struct root_domain, rcu);

	cpupri_cleanup(&rd->cpupri);
	free_cpumask_var(rd->rto_mask);
	free_cpumask_var(rd->online);
	free_cpumask_var(rd->span);
	kfree(rd);
}
