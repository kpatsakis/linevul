wait_for_completion_timeout(struct completion *x, unsigned long timeout)
{
	return wait_for_common(x, timeout, TASK_UNINTERRUPTIBLE);
}
