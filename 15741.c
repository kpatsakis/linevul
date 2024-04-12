static int add_to_pagemap(unsigned long addr, u64 pfn,
			  struct pagemapread *pm)
{
	pm->buffer[pm->pos++] = pfn;
	if (pm->pos >= pm->len)
		return PM_END_OF_BUFFER;
	return 0;
}
