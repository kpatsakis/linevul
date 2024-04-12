static long setup_trampoline(unsigned int syscall, unsigned int __user *tramp)
{
	int i;
	long err = 0;

	/* addi r1, r1, __SIGNAL_FRAMESIZE  # Pop the dummy stackframe */
	err |= __put_user(0x38210000UL | (__SIGNAL_FRAMESIZE & 0xffff), &tramp[0]);
	/* li r0, __NR_[rt_]sigreturn| */
	err |= __put_user(0x38000000UL | (syscall & 0xffff), &tramp[1]);
	/* sc */
	err |= __put_user(0x44000002UL, &tramp[2]);

	/* Minimal traceback info */
	for (i=TRAMP_TRACEBACK; i < TRAMP_SIZE ;i++)
		err |= __put_user(0, &tramp[i]);

	if (!err)
		flush_icache_range((unsigned long) &tramp[0],
			   (unsigned long) &tramp[TRAMP_SIZE]);

	return err;
}
