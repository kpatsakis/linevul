int make_pages_present(unsigned long addr, unsigned long end)
{
	int ret, len, write;
	struct vm_area_struct * vma;

	vma = find_vma(current->mm, addr);
	if (!vma)
		return -ENOMEM;
	/*
	 * We want to touch writable mappings with a write fault in order
	 * to break COW, except for shared mappings because these don't COW
	 * and we would not want to dirty them for nothing.
	 */
	write = (vma->vm_flags & (VM_WRITE | VM_SHARED)) == VM_WRITE;
	BUG_ON(addr >= end);
	BUG_ON(end > vma->vm_end);
	len = DIV_ROUND_UP(end, PAGE_SIZE) - addr/PAGE_SIZE;
	ret = get_user_pages(current, current->mm, addr,
			len, write, 0, NULL, NULL);
	if (ret < 0)
		return ret;
	return ret == len ? 0 : -EFAULT;
}
