static void truncate_hugepages(struct inode *inode, loff_t lstart)
{
	struct hstate *h = hstate_inode(inode);
	struct address_space *mapping = &inode->i_data;
	const pgoff_t start = lstart >> huge_page_shift(h);
	struct pagevec pvec;
	pgoff_t next;
	int i, freed = 0;

	pagevec_init(&pvec, 0);
	next = start;
	while (1) {
		if (!pagevec_lookup(&pvec, mapping, next, PAGEVEC_SIZE)) {
			if (next == start)
				break;
			next = start;
			continue;
		}

		for (i = 0; i < pagevec_count(&pvec); ++i) {
			struct page *page = pvec.pages[i];

			lock_page(page);
			if (page->index > next)
				next = page->index;
			++next;
			truncate_huge_page(page);
			unlock_page(page);
			freed++;
		}
		huge_pagevec_release(&pvec);
	}
	BUG_ON(!lstart && mapping->nrpages);
	hugetlb_unreserve_pages(inode, start, freed);
}
