void __init early_trap_init(void)
{
	set_intr_gate_ist(X86_TRAP_DB, &debug, DEBUG_STACK);
	/* int3 can be called from all */
	set_system_intr_gate_ist(X86_TRAP_BP, &int3, DEBUG_STACK);
#ifdef CONFIG_X86_32
	set_intr_gate(X86_TRAP_PF, page_fault);
#endif
	load_idt(&idt_descr);
}
