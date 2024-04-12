static int set_user_msr(struct task_struct *task, unsigned long msr)
{
	task->thread.regs->msr &= ~MSR_DEBUGCHANGE;
	task->thread.regs->msr |= msr & MSR_DEBUGCHANGE;
	return 0;
}
