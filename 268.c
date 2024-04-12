static struct page *alloc_surplus_huge_page(struct hstate *h, gfp_t gfp_mask,
		int nid, nodemask_t *nmask)
{
	struct page *page = NULL;

	if (hstate_is_gigantic(h))
		return NULL;

	spin_lock(&hugetlb_lock);
	if (h->surplus_huge_pages >= h->nr_overcommit_huge_pages)
		goto out_unlock;
	spin_unlock(&hugetlb_lock);

	page = alloc_fresh_huge_page(h, gfp_mask, nid, nmask);
	if (!page)
		return NULL;

	spin_lock(&hugetlb_lock);
	/*
	 * We could have raced with the pool size change.
	 * Double check that and simply deallocate the new page
	 * if we would end up overcommiting the surpluses. Abuse
	 * temporary page to workaround the nasty free_huge_page
	 * codeflow
	 */
	if (h->surplus_huge_pages >= h->nr_overcommit_huge_pages) {
		SetPageHugeTemporary(page);
		put_page(page);
		page = NULL;
	} else {
		h->surplus_huge_pages++;
		h->surplus_huge_pages_node[page_to_nid(page)]++;
	}

out_unlock:
	spin_unlock(&hugetlb_lock);

	return page;
}
