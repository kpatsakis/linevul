int ptrace_get_breakpoints(struct task_struct *tsk)
{
	if (atomic_inc_not_zero(&tsk->ptrace_bp_refcnt))
		return 0;

	return -1;
}
