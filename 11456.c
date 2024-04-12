void sched_destroy_group(struct task_group *tg)
{
	unsigned long flags;
	int i;

	/* end participation in shares distribution */
	for_each_possible_cpu(i)
		unregister_fair_sched_group(tg, i);

	spin_lock_irqsave(&task_group_lock, flags);
	list_del_rcu(&tg->list);
	list_del_rcu(&tg->siblings);
	spin_unlock_irqrestore(&task_group_lock, flags);

	/* wait for possible concurrent references to cfs_rqs complete */
	call_rcu(&tg->rcu, free_sched_group_rcu);
}
