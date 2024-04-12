static long ppc_del_hwdebug(struct task_struct *child, long addr, long data)
{
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
	int rc;

	if (data <= 4)
		rc = del_instruction_bp(child, (int)data);
	else
		rc = del_dac(child, (int)data - 4);

	if (!rc) {
		if (!DBCR_ACTIVE_EVENTS(child->thread.dbcr0,
					child->thread.dbcr1)) {
			child->thread.dbcr0 &= ~DBCR0_IDM;
			child->thread.regs->msr &= ~MSR_DE;
		}
	}
	return rc;
#else
	if (data != 1)
		return -EINVAL;
	if (child->thread.dabr == 0)
		return -ENOENT;

	child->thread.dabr = 0;

	return 0;
#endif
}
