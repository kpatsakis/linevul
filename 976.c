SYSCALL_DEFINE1(mlockall, int, flags)
{
	unsigned long lock_limit;
	int ret = -EINVAL;

	if (!flags || (flags & ~(MCL_CURRENT | MCL_FUTURE)))
		goto out;

	ret = -EPERM;
	if (!can_do_mlock())
		goto out;

	if (flags & MCL_CURRENT)
		lru_add_drain_all();	/* flush pagevec */

	lock_limit = rlimit(RLIMIT_MEMLOCK);
	lock_limit >>= PAGE_SHIFT;

	ret = -ENOMEM;
	down_write(&current->mm->mmap_sem);

	if (!(flags & MCL_CURRENT) || (current->mm->total_vm <= lock_limit) ||
	    capable(CAP_IPC_LOCK))
		ret = do_mlockall(flags);
	up_write(&current->mm->mmap_sem);
	if (!ret && (flags & MCL_CURRENT))
		mm_populate(0, TASK_SIZE);
out:
	return ret;
}
