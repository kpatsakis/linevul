task_function_call(struct task_struct *p, int (*func) (void *info), void *info)
{
	struct remote_function_call data = {
		.p	= p,
		.func	= func,
		.info	= info,
		.ret	= -ESRCH, /* No such (running) process */
	};

	if (task_curr(p))
		smp_call_function_single(task_cpu(p), remote_function, &data, 1);

	return data.ret;
}
