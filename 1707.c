static inline void advance(struct pt_regs *regs)
{
	regs->tpc   = regs->tnpc;
	regs->tnpc += 4;
	if (test_thread_flag(TIF_32BIT)) {
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	}
}
