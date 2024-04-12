analyze_stack(int cpu, struct task_struct *task, unsigned long *stack,
	      unsigned long **stack_end, unsigned long *irq_stack,
	      unsigned *used, char **id)
{
	unsigned long addr;

	addr = ((unsigned long)stack & (~(THREAD_SIZE - 1)));
	if ((unsigned long)task_stack_page(task) == addr)
		return STACK_IS_NORMAL;

	*stack_end = in_exception_stack(cpu, (unsigned long)stack,
					used, id);
	if (*stack_end)
		return STACK_IS_EXCEPTION;

	if (!irq_stack)
		return STACK_IS_NORMAL;

	*stack_end = irq_stack;
	irq_stack = irq_stack - irq_stack_size;

	if (in_irq_stack(stack, irq_stack, *stack_end))
		return STACK_IS_IRQ;

	return STACK_IS_UNKNOWN;
}
