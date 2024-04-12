static inline unsigned long get_vflags(struct kernel_vm86_regs *regs)
{
	unsigned long flags = regs->pt.flags & RETURN_MASK;

	if (VEFLAGS & X86_EFLAGS_VIF)
		flags |= X86_EFLAGS_IF;
	flags |= X86_EFLAGS_IOPL;
	return flags | (VEFLAGS & current->thread.v86mask);
}
