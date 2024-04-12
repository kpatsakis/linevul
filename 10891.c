void remove_from_page_cache(struct page *page)
{
	struct address_space *mapping = page->mapping;

	BUG_ON(!PageLocked(page));

	write_lock_irq(&mapping->tree_lock);
	__remove_from_page_cache(page);
	write_unlock_irq(&mapping->tree_lock);
}
