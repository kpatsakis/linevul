static void do_fault_siginfo(int code, int sig, struct pt_regs *regs,
			     unsigned int insn, int fault_code)
{
	unsigned long addr;
	siginfo_t info;

	info.si_code = code;
	info.si_signo = sig;
	info.si_errno = 0;
	if (fault_code & FAULT_CODE_ITLB)
		addr = regs->tpc;
	else
		addr = compute_effective_address(regs, insn, 0);
	info.si_addr = (void __user *) addr;
	info.si_trapno = 0;

	if (unlikely(show_unhandled_signals))
		show_signal_msg(regs, sig, code, addr, current);

	force_sig_info(sig, &info, current);
}
