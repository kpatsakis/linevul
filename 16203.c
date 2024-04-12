static int ptrace_do_wait(struct task_struct *tsk, int *notask_error,
			  enum pid_type type, struct pid *pid, int options,
			  struct siginfo __user *infop, int __user *stat_addr,
			  struct rusage __user *ru)
{
	struct task_struct *p;

	/*
	 * Traditionally we see ptrace'd stopped tasks regardless of options.
	 */
	options |= WUNTRACED;

	list_for_each_entry(p, &tsk->ptraced, ptrace_entry) {
		int ret = wait_consider_task(tsk, 1, p, notask_error,
					     type, pid, options,
					     infop, stat_addr, ru);
		if (ret)
			return ret;
	}

	return 0;
}
