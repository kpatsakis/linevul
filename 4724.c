long get_user_pages_longterm(unsigned long start, unsigned long nr_pages,
		unsigned int gup_flags, struct page **pages,
		struct vm_area_struct **vmas_arg)
{
	struct vm_area_struct **vmas = vmas_arg;
	struct vm_area_struct *vma_prev = NULL;
	long rc, i;

	if (!pages)
		return -EINVAL;

	if (!vmas) {
		vmas = kcalloc(nr_pages, sizeof(struct vm_area_struct *),
			       GFP_KERNEL);
		if (!vmas)
			return -ENOMEM;
	}

	rc = get_user_pages(start, nr_pages, gup_flags, pages, vmas);

	for (i = 0; i < rc; i++) {
		struct vm_area_struct *vma = vmas[i];

		if (vma == vma_prev)
			continue;

		vma_prev = vma;

		if (vma_is_fsdax(vma))
			break;
	}

	/*
	 * Either get_user_pages() failed, or the vma validation
	 * succeeded, in either case we don't need to put_page() before
	 * returning.
	 */
	if (i >= rc)
		goto out;

	for (i = 0; i < rc; i++)
		put_page(pages[i]);
	rc = -EOPNOTSUPP;
out:
	if (vmas != vmas_arg)
		kfree(vmas);
	return rc;
}
