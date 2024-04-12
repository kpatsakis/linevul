static void free_area(struct pstore *ps)
{
	if (ps->area)
		vfree(ps->area);
	ps->area = NULL;

	if (ps->zero_area)
		vfree(ps->zero_area);
	ps->zero_area = NULL;

	if (ps->header_area)
		vfree(ps->header_area);
	ps->header_area = NULL;
}
