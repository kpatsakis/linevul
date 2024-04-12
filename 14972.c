static void prep_compound_huge_page(struct page *page, int order)
{
	if (unlikely(order > (MAX_ORDER - 1)))
		prep_compound_gigantic_page(page, order);
	else
		prep_compound_page(page, order);
}
