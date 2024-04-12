static inline long check_and_migrate_cma_pages(unsigned long start, long nr_pages,
					       unsigned int gup_flags,
					       struct page **pages,
					       struct vm_area_struct **vmas)
{
	return nr_pages;
}
