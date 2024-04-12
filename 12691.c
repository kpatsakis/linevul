static int vfp_get(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   void *kbuf, void __user *ubuf)
{
	int ret;
	struct thread_info *thread = task_thread_info(target);
	struct vfp_hard_struct const *vfp = &thread->vfpstate.hard;
	const size_t user_fpregs_offset = offsetof(struct user_vfp, fpregs);
	const size_t user_fpscr_offset = offsetof(struct user_vfp, fpscr);

	vfp_sync_hwstate(thread);

	ret = user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				  &vfp->fpregs,
				  user_fpregs_offset,
				  user_fpregs_offset + sizeof(vfp->fpregs));
	if (ret)
		return ret;

	ret = user_regset_copyout_zero(&pos, &count, &kbuf, &ubuf,
				       user_fpregs_offset + sizeof(vfp->fpregs),
				       user_fpscr_offset);
	if (ret)
		return ret;

	return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				   &vfp->fpscr,
				   user_fpscr_offset,
				   user_fpscr_offset + sizeof(vfp->fpscr));
}
