static enum s_alloc __visit_domain_allocation_hell(struct s_data *d,
						   const struct cpumask *cpu_map)
{
#ifdef CONFIG_NUMA
	if (!alloc_cpumask_var(&d->domainspan, GFP_KERNEL))
		return sa_none;
	if (!alloc_cpumask_var(&d->covered, GFP_KERNEL))
		return sa_domainspan;
	if (!alloc_cpumask_var(&d->notcovered, GFP_KERNEL))
		return sa_covered;
	/* Allocate the per-node list of sched groups */
	d->sched_group_nodes = kcalloc(nr_node_ids,
				      sizeof(struct sched_group *), GFP_KERNEL);
	if (!d->sched_group_nodes) {
		printk(KERN_WARNING "Can not alloc sched group node list\n");
		return sa_notcovered;
	}
	sched_group_nodes_bycpu[cpumask_first(cpu_map)] = d->sched_group_nodes;
#endif
	if (!alloc_cpumask_var(&d->nodemask, GFP_KERNEL))
		return sa_sched_group_nodes;
	if (!alloc_cpumask_var(&d->this_sibling_map, GFP_KERNEL))
		return sa_nodemask;
	if (!alloc_cpumask_var(&d->this_core_map, GFP_KERNEL))
		return sa_this_sibling_map;
	if (!alloc_cpumask_var(&d->this_book_map, GFP_KERNEL))
		return sa_this_core_map;
	if (!alloc_cpumask_var(&d->send_covered, GFP_KERNEL))
		return sa_this_book_map;
	if (!alloc_cpumask_var(&d->tmpmask, GFP_KERNEL))
		return sa_send_covered;
	d->rd = alloc_rootdomain();
	if (!d->rd) {
		printk(KERN_WARNING "Cannot alloc root domain\n");
		return sa_tmpmask;
	}
	return sa_rootdomain;
}
