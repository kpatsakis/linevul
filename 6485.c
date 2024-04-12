static inline void clear_TF(struct kernel_vm86_regs *regs)
{
	regs->pt.flags &= ~X86_EFLAGS_TF;
}
