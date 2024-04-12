asmlinkage void do_address_error(struct pt_regs *regs,
				 unsigned long writeaccess,
				 unsigned long address)
{
	unsigned long error_code = 0;
	mm_segment_t oldfs;
	siginfo_t info;
	insn_size_t instruction;
	int tmp;

	/* Intentional ifdef */
#ifdef CONFIG_CPU_HAS_SR_RB
	error_code = lookup_exception_vector();
#endif

	oldfs = get_fs();

	if (user_mode(regs)) {
		int si_code = BUS_ADRERR;
		unsigned int user_action;

		local_irq_enable();
		inc_unaligned_user_access();

		set_fs(USER_DS);
		if (copy_from_user(&instruction, (insn_size_t *)(regs->pc & ~1),
				   sizeof(instruction))) {
			set_fs(oldfs);
			goto uspace_segv;
		}
		set_fs(oldfs);

		/* shout about userspace fixups */
		unaligned_fixups_notify(current, instruction, regs);

		user_action = unaligned_user_action();
		if (user_action & UM_FIXUP)
			goto fixup;
		if (user_action & UM_SIGNAL)
			goto uspace_segv;
		else {
			/* ignore */
			regs->pc += instruction_size(instruction);
			return;
		}

fixup:
		/* bad PC is not something we can fix */
		if (regs->pc & 1) {
			si_code = BUS_ADRALN;
			goto uspace_segv;
		}

		set_fs(USER_DS);
		tmp = handle_unaligned_access(instruction, regs,
					      &user_mem_access, 0,
					      address);
		set_fs(oldfs);

		if (tmp == 0)
			return; /* sorted */
uspace_segv:
		printk(KERN_NOTICE "Sending SIGBUS to \"%s\" due to unaligned "
		       "access (PC %lx PR %lx)\n", current->comm, regs->pc,
		       regs->pr);

		info.si_signo = SIGBUS;
		info.si_errno = 0;
		info.si_code = si_code;
		info.si_addr = (void __user *)address;
		force_sig_info(SIGBUS, &info, current);
	} else {
		inc_unaligned_kernel_access();

		if (regs->pc & 1)
			die("unaligned program counter", regs, error_code);

		set_fs(KERNEL_DS);
		if (copy_from_user(&instruction, (void __user *)(regs->pc),
				   sizeof(instruction))) {
			/* Argh. Fault on the instruction itself.
			   This should never happen non-SMP
			*/
			set_fs(oldfs);
			die("insn faulting in do_address_error", regs, 0);
		}

		unaligned_fixups_notify(current, instruction, regs);

		handle_unaligned_access(instruction, regs, &user_mem_access,
					0, address);
		set_fs(oldfs);
	}
}
