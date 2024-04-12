long get_user_pages_longterm(unsigned long start, unsigned long nr_pages,
			     unsigned int gup_flags, struct page **pages,
			     struct vm_area_struct **vmas_arg)
{
	struct vm_area_struct **vmas = vmas_arg;
	unsigned long flags;
	long rc, i;

	if (!pages)
		return -EINVAL;

	if (!vmas) {
		vmas = kcalloc(nr_pages, sizeof(struct vm_area_struct *),
			       GFP_KERNEL);
		if (!vmas)
			return -ENOMEM;
	}

	flags = memalloc_nocma_save();
	rc = get_user_pages(start, nr_pages, gup_flags, pages, vmas);
	memalloc_nocma_restore(flags);
	if (rc < 0)
		goto out;

	if (check_dax_vmas(vmas, rc)) {
		for (i = 0; i < rc; i++)
			put_page(pages[i]);
		rc = -EOPNOTSUPP;
		goto out;
	}

	rc = check_and_migrate_cma_pages(start, rc, gup_flags, pages, vmas);
out:
	if (vmas != vmas_arg)
		kfree(vmas);
	return rc;
}
