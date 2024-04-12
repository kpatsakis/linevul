SYSCALL_DEFINE1(sigpending, old_sigset_t __user *, set)
{
	return sys_rt_sigpending((sigset_t __user *)set, sizeof(old_sigset_t)); 
}
