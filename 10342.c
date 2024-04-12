void __online_page_set_limits(struct page *page)
{
	unsigned long pfn = page_to_pfn(page);

	if (pfn >= num_physpages)
		num_physpages = pfn + 1;
}
