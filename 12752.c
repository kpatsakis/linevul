SYSCALL_DEFINE5(waitid, int, which, pid_t, upid, struct siginfo __user *,
		infop, int, options, struct rusage __user *, ru)
{
	struct wait_opts wo;
	struct pid *pid = NULL;
	enum pid_type type;
	long ret;

	if (options & ~(WNOHANG|WNOWAIT|WEXITED|WSTOPPED|WCONTINUED))
		return -EINVAL;
	if (!(options & (WEXITED|WSTOPPED|WCONTINUED)))
		return -EINVAL;

	switch (which) {
	case P_ALL:
		type = PIDTYPE_MAX;
		break;
	case P_PID:
		type = PIDTYPE_PID;
		if (upid <= 0)
			return -EINVAL;
		break;
	case P_PGID:
		type = PIDTYPE_PGID;
		if (upid <= 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	if (type < PIDTYPE_MAX)
		pid = find_get_pid(upid);

	wo.wo_type	= type;
	wo.wo_pid	= pid;
	wo.wo_flags	= options;
	wo.wo_info	= infop;
	wo.wo_stat	= NULL;
	wo.wo_rusage	= ru;
	ret = do_wait(&wo);

	if (ret > 0) {
		ret = 0;
	} else if (infop) {
		/*
		 * For a WNOHANG return, clear out all the fields
		 * we would set so the user can easily tell the
		 * difference.
		 */
		if (!ret)
			ret = put_user(0, &infop->si_signo);
		if (!ret)
			ret = put_user(0, &infop->si_errno);
		if (!ret)
			ret = put_user(0, &infop->si_code);
		if (!ret)
			ret = put_user(0, &infop->si_pid);
		if (!ret)
			ret = put_user(0, &infop->si_uid);
		if (!ret)
			ret = put_user(0, &infop->si_status);
	}

	put_pid(pid);

	/* avoid REGPARM breakage on x86: */
	asmlinkage_protect(5, ret, which, upid, infop, options, ru);
	return ret;
}
