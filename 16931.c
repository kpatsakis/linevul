COMPAT_SYSCALL_DEFINE2(timerfd_gettime, int, ufd,
		struct compat_itimerspec __user *, otmr)
{
	struct itimerspec kotmr;
	int ret = do_timerfd_gettime(ufd, &kotmr);
	if (ret)
		return ret;
	return put_compat_itimerspec(otmr, &kotmr) ? -EFAULT: 0;
}
