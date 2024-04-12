void __init trap_init(void)
{
	set_exception_table_vec(TRAP_RESERVED_INST, do_reserved_inst);
	set_exception_table_vec(TRAP_ILLEGAL_SLOT_INST, do_illegal_slot_inst);

#if defined(CONFIG_CPU_SH4) && !defined(CONFIG_SH_FPU) || \
    defined(CONFIG_SH_FPU_EMU)
	/*
	 * For SH-4 lacking an FPU, treat floating point instructions as
	 * reserved. They'll be handled in the math-emu case, or faulted on
	 * otherwise.
	 */
	set_exception_table_evt(0x800, do_reserved_inst);
	set_exception_table_evt(0x820, do_illegal_slot_inst);
#elif defined(CONFIG_SH_FPU)
	set_exception_table_evt(0x800, fpu_state_restore_trap_handler);
	set_exception_table_evt(0x820, fpu_state_restore_trap_handler);
#endif

#ifdef CONFIG_CPU_SH2
	set_exception_table_vec(TRAP_ADDRESS_ERROR, address_error_trap_handler);
#endif
#ifdef CONFIG_CPU_SH2A
	set_exception_table_vec(TRAP_DIVZERO_ERROR, do_divide_error);
	set_exception_table_vec(TRAP_DIVOVF_ERROR, do_divide_error);
#ifdef CONFIG_SH_FPU
	set_exception_table_vec(TRAP_FPU_ERROR, fpu_error_trap_handler);
#endif
#endif

#ifdef TRAP_UBC
	set_exception_table_vec(TRAP_UBC, breakpoint_trap_handler);
#endif
}
