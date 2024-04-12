int sys_vm86old(struct vm86_struct __user *v86, struct pt_regs *regs)
{
	struct kernel_vm86_struct info; /* declare this _on top_,
					 * this avoids wasting of stack space.
					 * This remains on the stack until we
					 * return to 32 bit user space.
					 */
	struct task_struct *tsk;
	int tmp, ret = -EPERM;

	tsk = current;
	if (tsk->thread.saved_sp0)
		goto out;
	tmp = copy_vm86_regs_from_user(&info.regs, &v86->regs,
				       offsetof(struct kernel_vm86_struct, vm86plus) -
				       sizeof(info.regs));
	ret = -EFAULT;
	if (tmp)
		goto out;
	memset(&info.vm86plus, 0, (int)&info.regs32 - (int)&info.vm86plus);
	info.regs32 = regs;
	tsk->thread.vm86_info = v86;
	do_sys_vm86(&info, tsk);
	ret = 0;	/* we never return here */
out:
	return ret;
}
