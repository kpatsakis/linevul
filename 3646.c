static int bpf_prog_charge_memlock(struct bpf_prog *prog)
{
	struct user_struct *user = get_current_user();
	unsigned long memlock_limit;

	memlock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	atomic_long_add(prog->pages, &user->locked_vm);
	if (atomic_long_read(&user->locked_vm) > memlock_limit) {
		atomic_long_sub(prog->pages, &user->locked_vm);
		free_uid(user);
		return -EPERM;
	}
	prog->aux->user = user;
	return 0;
}
