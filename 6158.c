unsigned long regs_get_register(struct pt_regs *regs, unsigned int offset)
{
	if (offset >= NUM_GPRS)
		return 0;
	return regs->gprs[offset];
}
