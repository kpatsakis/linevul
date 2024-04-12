int fpregs_get(struct task_struct *target,
	       const struct user_regset *regset,
	       unsigned int pos, unsigned int count,
	       void *kbuf, void __user *ubuf)
{
	int ret;

	ret = init_fpu(target);
	if (ret)
		return ret;

	if ((boot_cpu_data.flags & CPU_HAS_FPU))
		return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
					   &target->thread.xstate->hardfpu, 0, -1);

	return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				   &target->thread.xstate->softfpu, 0, -1);
}
