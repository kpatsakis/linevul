static int ptrace_write_user(struct task_struct *tsk, unsigned long off,
			     unsigned long val)
{
	if (off & 3 || off >= sizeof(struct user))
		return -EIO;

	if (off >= sizeof(struct pt_regs))
		return 0;

	return put_user_reg(tsk, off >> 2, val);
}
