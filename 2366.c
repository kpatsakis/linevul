static struct syscall_metadata *syscall_nr_to_meta(int nr)
{
	if (!syscalls_metadata || nr >= NR_syscalls || nr < 0)
		return NULL;

	return syscalls_metadata[nr];
}
