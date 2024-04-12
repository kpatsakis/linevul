static int ptrace_read_user(struct task_struct *tsk, unsigned long off,
			    unsigned long __user *ret)
{
	unsigned long tmp;

	if (off & 3)
		return -EIO;

	tmp = 0;
	if (off == PT_TEXT_ADDR)
		tmp = tsk->mm->start_code;
	else if (off == PT_DATA_ADDR)
		tmp = tsk->mm->start_data;
	else if (off == PT_TEXT_END_ADDR)
		tmp = tsk->mm->end_code;
	else if (off < sizeof(struct pt_regs))
		tmp = get_user_reg(tsk, off >> 2);
	else if (off >= sizeof(struct user))
		return -EIO;

	return put_user(tmp, ret);
}
