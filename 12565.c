void perf_callchain_kernel(struct perf_callchain_entry *entry,
			   struct pt_regs *regs)
{
	unsigned long ksp, fp;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	int graph = 0;
#endif

	stack_trace_flush();

	perf_callchain_store(entry, regs->tpc);

	ksp = regs->u_regs[UREG_I6];
	fp = ksp + STACK_BIAS;
	do {
		struct sparc_stackf *sf;
		struct pt_regs *regs;
		unsigned long pc;

		if (!kstack_valid(current_thread_info(), fp))
			break;

		sf = (struct sparc_stackf *) fp;
		regs = (struct pt_regs *) (sf + 1);

		if (kstack_is_trap_frame(current_thread_info(), regs)) {
			if (user_mode(regs))
				break;
			pc = regs->tpc;
			fp = regs->u_regs[UREG_I6] + STACK_BIAS;
		} else {
			pc = sf->callers_pc;
			fp = (unsigned long)sf->fp + STACK_BIAS;
		}
		perf_callchain_store(entry, pc);
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
		if ((pc + 8UL) == (unsigned long) &return_to_handler) {
			int index = current->curr_ret_stack;
			if (current->ret_stack && index >= graph) {
				pc = current->ret_stack[index - graph].ret;
				perf_callchain_store(entry, pc);
				graph++;
			}
		}
#endif
	} while (entry->nr < PERF_MAX_STACK_DEPTH);
}
