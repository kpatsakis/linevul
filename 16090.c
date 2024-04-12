static void smaps_pte_entry(pte_t ptent, unsigned long addr,
		unsigned long ptent_size, struct mm_walk *walk)
{
	struct mem_size_stats *mss = walk->private;
	struct vm_area_struct *vma = mss->vma;
	struct page *page;
	int mapcount;

	if (is_swap_pte(ptent)) {
		mss->swap += ptent_size;
		return;
	}

	if (!pte_present(ptent))
		return;

	page = vm_normal_page(vma, addr, ptent);
	if (!page)
		return;

	if (PageAnon(page))
		mss->anonymous += ptent_size;

	mss->resident += ptent_size;
	/* Accumulate the size in pages that have been accessed. */
	if (pte_young(ptent) || PageReferenced(page))
		mss->referenced += ptent_size;
	mapcount = page_mapcount(page);
	if (mapcount >= 2) {
		if (pte_dirty(ptent) || PageDirty(page))
			mss->shared_dirty += ptent_size;
		else
			mss->shared_clean += ptent_size;
		mss->pss += (ptent_size << PSS_SHIFT) / mapcount;
	} else {
		if (pte_dirty(ptent) || PageDirty(page))
			mss->private_dirty += ptent_size;
		else
			mss->private_clean += ptent_size;
		mss->pss += (ptent_size << PSS_SHIFT);
	}
}
