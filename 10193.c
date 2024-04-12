static int __perf_cgroup_move(void *info)
{
	struct task_struct *task = info;
	rcu_read_lock();
	perf_cgroup_switch(task, PERF_CGROUP_SWOUT | PERF_CGROUP_SWIN);
	rcu_read_unlock();
	return 0;
}
