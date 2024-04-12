static enum bp_state decrease_reservation(unsigned long nr_pages, gfp_t gfp)
{
	enum bp_state state = BP_DONE;
	unsigned long i;
	struct page *page, *tmp;
	int ret;
	LIST_HEAD(pages);

	if (nr_pages > ARRAY_SIZE(frame_list))
		nr_pages = ARRAY_SIZE(frame_list);

	for (i = 0; i < nr_pages; i++) {
		page = alloc_page(gfp);
		if (page == NULL) {
			nr_pages = i;
			state = BP_EAGAIN;
			break;
		}
		__SetPageOffline(page);
		adjust_managed_page_count(page, -1);
		xenmem_reservation_scrub_page(page);
		list_add(&page->lru, &pages);
	}

	/*
	 * Ensure that ballooned highmem pages don't have kmaps.
	 *
	 * Do this before changing the p2m as kmap_flush_unused()
	 * reads PTEs to obtain pages (and hence needs the original
	 * p2m entry).
	 */
	kmap_flush_unused();

	/*
	 * Setup the frame, update direct mapping, invalidate P2M,
	 * and add to balloon.
	 */
	i = 0;
	list_for_each_entry_safe(page, tmp, &pages, lru) {
		frame_list[i++] = xen_page_to_gfn(page);

		xenmem_reservation_va_mapping_reset(1, &page);

		list_del(&page->lru);

		balloon_append(page);
	}

	flush_tlb_all();

	ret = xenmem_reservation_decrease(nr_pages, frame_list);
	BUG_ON(ret != nr_pages);

	balloon_stats.current_pages -= nr_pages;

	return state;
}
