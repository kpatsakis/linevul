asmlinkage void do_mdmx(struct pt_regs *regs)
{
	force_sig(SIGILL, current);
}
