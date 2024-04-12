static int pagemap_hugetlb_range(pte_t *pte, unsigned long hmask,
				 unsigned long addr, unsigned long end,
				 struct mm_walk *walk)
{
	struct pagemapread *pm = walk->private;
	int err = 0;
	u64 pfn;

	for (; addr != end; addr += PAGE_SIZE) {
		int offset = (addr & ~hmask) >> PAGE_SHIFT;
		pfn = huge_pte_to_pagemap_entry(*pte, offset);
		err = add_to_pagemap(addr, pfn, pm);
		if (err)
			return err;
	}

	cond_resched();

	return err;
}
