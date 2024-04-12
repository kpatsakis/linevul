static void __unhash_process(struct task_struct *p)
{
	nr_threads--;
	detach_pid(p, PIDTYPE_PID);
	if (thread_group_leader(p)) {
		detach_pid(p, PIDTYPE_PGID);
		detach_pid(p, PIDTYPE_SID);

		list_del_rcu(&p->tasks);
		__get_cpu_var(process_counts)--;
	}
	list_del_rcu(&p->thread_group);
	list_del_init(&p->sibling);
}
