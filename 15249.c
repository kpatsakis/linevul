group_type group_classify(struct sched_group *group,
			  struct sg_lb_stats *sgs)
{
	if (sgs->group_no_capacity)
		return group_overloaded;

	if (sg_imbalanced(group))
		return group_imbalanced;

	if (sgs->group_misfit_task_load)
		return group_misfit_task;

	return group_other;
}
