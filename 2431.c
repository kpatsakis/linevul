void kgdb_arch_set_pc(struct pt_regs *regs, unsigned long ip)
{
	regs->ip = ip;
}
