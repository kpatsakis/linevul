asmlinkage long sys_waitpid(pid_t pid, int __user *stat_addr, int options)
{
	return sys_wait4(pid, stat_addr, options, NULL);
}
