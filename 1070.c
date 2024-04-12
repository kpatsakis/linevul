static struct vm_area_struct* hugetlb_vma(unsigned long addr, struct mm_walk *walk)
{
	struct vm_area_struct *vma;

	/* We don't need vma lookup at all. */
	if (!walk->hugetlb_entry)
		return NULL;

	VM_BUG_ON(!rwsem_is_locked(&walk->mm->mmap_sem));
	vma = find_vma(walk->mm, addr);
	if (vma && vma->vm_start <= addr && is_vm_hugetlb_page(vma))
		return vma;

	return NULL;
}
