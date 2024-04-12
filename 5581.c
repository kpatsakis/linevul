static struct page *alloc_fresh_huge_page_node(struct hstate *h, int nid)
{
	struct page *page;

	if (h->order >= MAX_ORDER)
		return NULL;

	page = alloc_pages_exact_node(nid,
		htlb_alloc_mask|__GFP_COMP|__GFP_THISNODE|
						__GFP_REPEAT|__GFP_NOWARN,
		huge_page_order(h));
	if (page) {
		if (arch_prepare_hugepage(page)) {
			__free_pages(page, huge_page_order(h));
			return NULL;
		}
		prep_new_huge_page(h, page, nid);
	}

	return page;
}
