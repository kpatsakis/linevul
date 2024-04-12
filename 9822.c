static long do_mbind(unsigned long start, unsigned long len,
		     unsigned short mode, unsigned short mode_flags,
		     nodemask_t *nmask, unsigned long flags)
{
	struct vm_area_struct *vma;
	struct mm_struct *mm = current->mm;
	struct mempolicy *new;
	unsigned long end;
	int err;
	LIST_HEAD(pagelist);

	if (flags & ~(unsigned long)(MPOL_MF_STRICT |
				     MPOL_MF_MOVE | MPOL_MF_MOVE_ALL))
		return -EINVAL;
	if ((flags & MPOL_MF_MOVE_ALL) && !capable(CAP_SYS_NICE))
		return -EPERM;

	if (start & ~PAGE_MASK)
		return -EINVAL;

	if (mode == MPOL_DEFAULT)
		flags &= ~MPOL_MF_STRICT;

	len = (len + PAGE_SIZE - 1) & PAGE_MASK;
	end = start + len;

	if (end < start)
		return -EINVAL;
	if (end == start)
		return 0;

	new = mpol_new(mode, mode_flags, nmask);
	if (IS_ERR(new))
		return PTR_ERR(new);

	/*
	 * If we are using the default policy then operation
	 * on discontinuous address spaces is okay after all
	 */
	if (!new)
		flags |= MPOL_MF_DISCONTIG_OK;

	pr_debug("mbind %lx-%lx mode:%d flags:%d nodes:%lx\n",
		 start, start + len, mode, mode_flags,
		 nmask ? nodes_addr(*nmask)[0] : -1);

	if (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) {

		err = migrate_prep();
		if (err)
			goto mpol_out;
	}
	{
		NODEMASK_SCRATCH(scratch);
		if (scratch) {
			down_write(&mm->mmap_sem);
			task_lock(current);
			err = mpol_set_nodemask(new, nmask, scratch);
			task_unlock(current);
			if (err)
				up_write(&mm->mmap_sem);
		} else
			err = -ENOMEM;
		NODEMASK_SCRATCH_FREE(scratch);
	}
	if (err)
		goto mpol_out;

	vma = check_range(mm, start, end, nmask,
			  flags | MPOL_MF_INVERT, &pagelist);

	err = PTR_ERR(vma);
	if (!IS_ERR(vma)) {
		int nr_failed = 0;

		err = mbind_range(mm, start, end, new);

		if (!list_empty(&pagelist)) {
			nr_failed = migrate_pages(&pagelist, new_vma_page,
						(unsigned long)vma,
						false, true);
			if (nr_failed)
				putback_lru_pages(&pagelist);
		}

		if (!err && nr_failed && (flags & MPOL_MF_STRICT))
			err = -EIO;
	} else
		putback_lru_pages(&pagelist);

	up_write(&mm->mmap_sem);
 mpol_out:
	mpol_put(new);
	return err;
}
