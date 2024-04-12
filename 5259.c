asmlinkage long do_syscall_trace_enter(struct pt_regs *regs)
{
	long ret = 0;

	/* Do the secure computing check first. */
	if (secure_computing(regs->gprs[2])) {
		/* seccomp failures shouldn't expose any additional code. */
		ret = -1;
		goto out;
	}

	/*
	 * The sysc_tracesys code in entry.S stored the system
	 * call number to gprs[2].
	 */
	if (test_thread_flag(TIF_SYSCALL_TRACE) &&
	    (tracehook_report_syscall_entry(regs) ||
	     regs->gprs[2] >= NR_syscalls)) {
		/*
		 * Tracing decided this syscall should not happen or the
		 * debugger stored an invalid system call number. Skip
		 * the system call and the system call restart handling.
		 */
		clear_pt_regs_flag(regs, PIF_SYSCALL);
		ret = -1;
	}

	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->gprs[2]);

	audit_syscall_entry(is_compat_task() ?
				AUDIT_ARCH_S390 : AUDIT_ARCH_S390X,
			    regs->gprs[2], regs->orig_gpr2,
			    regs->gprs[3], regs->gprs[4],
			    regs->gprs[5]);
out:
	return ret ?: regs->gprs[2];
}
