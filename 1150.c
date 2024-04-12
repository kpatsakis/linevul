struct mempolicy *get_vma_policy(struct task_struct *task,
		struct vm_area_struct *vma, unsigned long addr)
{
	struct mempolicy *pol = task->mempolicy;

	if (vma) {
		if (vma->vm_ops && vma->vm_ops->get_policy) {
			struct mempolicy *vpol = vma->vm_ops->get_policy(vma,
									addr);
			if (vpol)
				pol = vpol;
		} else if (vma->vm_policy)
			pol = vma->vm_policy;
	}
	if (!pol)
		pol = &default_policy;
	return pol;
}
