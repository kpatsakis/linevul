SYSCALL_DEFINE4(timerfd_settime, int, ufd, int, flags,
		const struct itimerspec __user *, utmr,
		struct itimerspec __user *, otmr)
{
	struct itimerspec new, old;
	int ret;

	if (copy_from_user(&new, utmr, sizeof(new)))
		return -EFAULT;
	ret = do_timerfd_settime(ufd, flags, &new, &old);
	if (ret)
		return ret;
	if (otmr && copy_to_user(otmr, &old, sizeof(old)))
		return -EFAULT;

	return ret;
}
