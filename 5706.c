int add_swap_count_continuation(swp_entry_t entry, gfp_t gfp_mask)
{
	struct swap_info_struct *si;
	struct page *head;
	struct page *page;
	struct page *list_page;
	pgoff_t offset;
	unsigned char count;

	/*
	 * When debugging, it's easier to use __GFP_ZERO here; but it's better
	 * for latency not to zero a page while GFP_ATOMIC and holding locks.
	 */
	page = alloc_page(gfp_mask | __GFP_HIGHMEM);

	si = swap_info_get(entry);
	if (!si) {
		/*
		 * An acceptable race has occurred since the failing
		 * __swap_duplicate(): the swap entry has been freed,
		 * perhaps even the whole swap_map cleared for swapoff.
		 */
		goto outer;
	}

	offset = swp_offset(entry);
	count = si->swap_map[offset] & ~SWAP_HAS_CACHE;

	if ((count & ~COUNT_CONTINUED) != SWAP_MAP_MAX) {
		/*
		 * The higher the swap count, the more likely it is that tasks
		 * will race to add swap count continuation: we need to avoid
		 * over-provisioning.
		 */
		goto out;
	}

	if (!page) {
		spin_unlock(&swap_lock);
		return -ENOMEM;
	}

	/*
	 * We are fortunate that although vmalloc_to_page uses pte_offset_map,
	 * no architecture is using highmem pages for kernel pagetables: so it
	 * will not corrupt the GFP_ATOMIC caller's atomic pagetable kmaps.
	 */
	head = vmalloc_to_page(si->swap_map + offset);
	offset &= ~PAGE_MASK;

	/*
	 * Page allocation does not initialize the page's lru field,
	 * but it does always reset its private field.
	 */
	if (!page_private(head)) {
		BUG_ON(count & COUNT_CONTINUED);
		INIT_LIST_HEAD(&head->lru);
		set_page_private(head, SWP_CONTINUED);
		si->flags |= SWP_CONTINUED;
	}

	list_for_each_entry(list_page, &head->lru, lru) {
		unsigned char *map;

		/*
		 * If the previous map said no continuation, but we've found
		 * a continuation page, free our allocation and use this one.
		 */
		if (!(count & COUNT_CONTINUED))
			goto out;

		map = kmap_atomic(list_page, KM_USER0) + offset;
		count = *map;
		kunmap_atomic(map, KM_USER0);

		/*
		 * If this continuation count now has some space in it,
		 * free our allocation and use this one.
		 */
		if ((count & ~COUNT_CONTINUED) != SWAP_CONT_MAX)
			goto out;
	}

	list_add_tail(&page->lru, &head->lru);
	page = NULL;			/* now it's attached, don't free it */
out:
	spin_unlock(&swap_lock);
outer:
	if (page)
		__free_page(page);
	return 0;
}
