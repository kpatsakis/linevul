void __sched wait_for_completion(struct completion *x)
{
	wait_for_common(x, MAX_SCHEDULE_TIMEOUT, TASK_UNINTERRUPTIBLE);
}
