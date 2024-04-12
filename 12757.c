static int ptrace_set_breakpoint_addr(struct task_struct *tsk, int nr,
				      unsigned long addr)
{
	struct perf_event *bp;
	struct thread_struct *t = &tsk->thread;
	struct perf_event_attr attr;
	int err = 0;

	if (ptrace_get_breakpoints(tsk) < 0)
		return -ESRCH;

	if (!t->ptrace_bps[nr]) {
		ptrace_breakpoint_init(&attr);
		/*
		 * Put stub len and type to register (reserve) an inactive but
		 * correct bp
		 */
		attr.bp_addr = addr;
		attr.bp_len = HW_BREAKPOINT_LEN_1;
		attr.bp_type = HW_BREAKPOINT_W;
		attr.disabled = 1;

		bp = register_user_hw_breakpoint(&attr, ptrace_triggered, tsk);

		/*
		 * CHECKME: the previous code returned -EIO if the addr wasn't
		 * a valid task virtual addr. The new one will return -EINVAL in
		 *  this case.
		 * -EINVAL may be what we want for in-kernel breakpoints users,
		 * but -EIO looks better for ptrace, since we refuse a register
		 * writing for the user. And anyway this is the previous
		 * behaviour.
		 */
		if (IS_ERR(bp)) {
			err = PTR_ERR(bp);
			goto put;
		}

		t->ptrace_bps[nr] = bp;
	} else {
		bp = t->ptrace_bps[nr];

		attr = bp->attr;
		attr.bp_addr = addr;
		err = modify_user_hw_breakpoint(bp, &attr);
	}

put:
	ptrace_put_breakpoints(tsk);
	return err;
}
