static int fpr_set(struct task_struct *target, const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __user *ubuf)
{
#ifdef CONFIG_VSX
	double buf[33];
	int i;
#endif
	flush_fp_to_thread(target);

#ifdef CONFIG_VSX
	/* copy to local buffer then write that out */
	i = user_regset_copyin(&pos, &count, &kbuf, &ubuf, buf, 0, -1);
	if (i)
		return i;
	for (i = 0; i < 32 ; i++)
		target->thread.TS_FPR(i) = buf[i];
	memcpy(&target->thread.fpscr, &buf[32], sizeof(double));
	return 0;
#else
	BUILD_BUG_ON(offsetof(struct thread_struct, fpscr) !=
		     offsetof(struct thread_struct, TS_FPR(32)));

	return user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &target->thread.fpr, 0, -1);
#endif
}
