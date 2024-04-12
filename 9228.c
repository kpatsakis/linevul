int kill_pid_info_as_uid(int sig, struct siginfo *info, struct pid *pid,
		      uid_t uid, uid_t euid, u32 secid)
{
	int ret = -EINVAL;
	struct task_struct *p;
	const struct cred *pcred;
	unsigned long flags;

	if (!valid_signal(sig))
		return ret;

	rcu_read_lock();
	p = pid_task(pid, PIDTYPE_PID);
	if (!p) {
		ret = -ESRCH;
		goto out_unlock;
	}
	pcred = __task_cred(p);
	if (si_fromuser(info) &&
	    euid != pcred->suid && euid != pcred->uid &&
	    uid  != pcred->suid && uid  != pcred->uid) {
		ret = -EPERM;
		goto out_unlock;
	}
	ret = security_task_kill(p, info, sig, secid);
	if (ret)
		goto out_unlock;

	if (sig) {
		if (lock_task_sighand(p, &flags)) {
			ret = __send_signal(sig, info, p, 1, 0);
			unlock_task_sighand(p, &flags);
		} else
			ret = -ESRCH;
	}
out_unlock:
	rcu_read_unlock();
	return ret;
}
