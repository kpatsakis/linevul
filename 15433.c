static inline void set_IF(struct kernel_vm86_regs *regs)
{
	VEFLAGS |= X86_EFLAGS_VIF;
	if (VEFLAGS & X86_EFLAGS_VIP)
		return_to_32bit(regs, VM86_STI);
}
