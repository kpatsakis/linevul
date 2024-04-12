static inline __u32 __peek_user_per_compat(struct task_struct *child,
					   addr_t addr)
{
	struct compat_per_struct_kernel *dummy32 = NULL;

	if (addr == (addr_t) &dummy32->cr9)
		/* Control bits of the active per set. */
		return (__u32) test_thread_flag(TIF_SINGLE_STEP) ?
			PER_EVENT_IFETCH : child->thread.per_user.control;
	else if (addr == (addr_t) &dummy32->cr10)
		/* Start address of the active per set. */
		return (__u32) test_thread_flag(TIF_SINGLE_STEP) ?
			0 : child->thread.per_user.start;
	else if (addr == (addr_t) &dummy32->cr11)
		/* End address of the active per set. */
		return test_thread_flag(TIF_SINGLE_STEP) ?
			PSW32_ADDR_INSN : child->thread.per_user.end;
	else if (addr == (addr_t) &dummy32->bits)
		/* Single-step bit. */
		return (__u32) test_thread_flag(TIF_SINGLE_STEP) ?
			0x80000000 : 0;
	else if (addr == (addr_t) &dummy32->starting_addr)
		/* Start address of the user specified per set. */
		return (__u32) child->thread.per_user.start;
	else if (addr == (addr_t) &dummy32->ending_addr)
		/* End address of the user specified per set. */
		return (__u32) child->thread.per_user.end;
	else if (addr == (addr_t) &dummy32->perc_atmid)
		/* PER code, ATMID and AI of the last PER trap */
		return (__u32) child->thread.per_event.cause << 16;
	else if (addr == (addr_t) &dummy32->address)
		/* Address of the last PER trap */
		return (__u32) child->thread.per_event.address;
	else if (addr == (addr_t) &dummy32->access_id)
		/* Access id of the last PER trap */
		return (__u32) child->thread.per_event.paid << 24;
	return 0;
}
