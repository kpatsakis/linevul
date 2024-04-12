void mpol_fix_fork_child_flag(struct task_struct *p)
{
	if (p->mempolicy)
		p->flags |= PF_MEMPOLICY;
	else
		p->flags &= ~PF_MEMPOLICY;
}
