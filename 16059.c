int migrate_huge_page_move_mapping(struct address_space *mapping,
				   struct page *newpage, struct page *page)
{
	int expected_count;
	void **pslot;

	spin_lock_irq(&mapping->tree_lock);

	pslot = radix_tree_lookup_slot(&mapping->page_tree,
					page_index(page));

	expected_count = 2 + page_has_private(page);
	if (page_count(page) != expected_count ||
		radix_tree_deref_slot_protected(pslot, &mapping->tree_lock) != page) {
		spin_unlock_irq(&mapping->tree_lock);
		return -EAGAIN;
	}

	if (!page_freeze_refs(page, expected_count)) {
		spin_unlock_irq(&mapping->tree_lock);
		return -EAGAIN;
	}

	set_page_memcg(newpage, page_memcg(page));
	newpage->index = page->index;
	newpage->mapping = page->mapping;
	get_page(newpage);

	radix_tree_replace_slot(pslot, newpage);

	page_unfreeze_refs(page, expected_count - 1);

	spin_unlock_irq(&mapping->tree_lock);
	return MIGRATEPAGE_SUCCESS;
}
