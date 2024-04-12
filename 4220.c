do_group_exit(int exit_code)
{
	struct signal_struct *sig = current->signal;

	BUG_ON(exit_code & 0x80); /* core dumps don't get here */

	if (signal_group_exit(sig))
		exit_code = sig->group_exit_code;
	else if (!thread_group_empty(current)) {
		struct sighand_struct *const sighand = current->sighand;
		spin_lock_irq(&sighand->siglock);
		if (signal_group_exit(sig))
			/* Another thread got here before we took the lock.  */
			exit_code = sig->group_exit_code;
		else {
			sig->group_exit_code = exit_code;
			sig->flags = SIGNAL_GROUP_EXIT;
			zap_other_threads(current);
		}
		spin_unlock_irq(&sighand->siglock);
	}

	do_exit(exit_code);
	/* NOTREACHED */
}
