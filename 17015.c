static inline int get_and_reset_irq(int irqnumber)
{
	int bit;
	unsigned long flags;
	int ret = 0;

	if (invalid_vm86_irq(irqnumber)) return 0;
	if (vm86_irqs[irqnumber].tsk != current) return 0;
	spin_lock_irqsave(&irqbits_lock, flags);
	bit = irqbits & (1 << irqnumber);
	irqbits &= ~bit;
	if (bit) {
		enable_irq(irqnumber);
		ret = 1;
	}

	spin_unlock_irqrestore(&irqbits_lock, flags);
	return ret;
}
