static void migrate_page_add(struct page *page, struct list_head *pagelist,
				unsigned long flags)
{
	/*
	 * Avoid migrating a page that is shared with others.
	 */
	if ((flags & MPOL_MF_MOVE_ALL) || page_mapcount(page) == 1) {
		if (!isolate_lru_page(page)) {
			list_add_tail(&page->lru, pagelist);
			inc_node_page_state(page, NR_ISOLATED_ANON +
					    page_is_file_cache(page));
		}
	}
}
