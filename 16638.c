static inline int check_pgd_range(struct vm_area_struct *vma,
		unsigned long addr, unsigned long end,
		const nodemask_t *nodes, unsigned long flags,
		void *private)
{
	pgd_t *pgd;
	unsigned long next;

	pgd = pgd_offset(vma->vm_mm, addr);
	do {
		next = pgd_addr_end(addr, end);
		if (pgd_none_or_clear_bad(pgd))
			continue;
		if (check_pud_range(vma, pgd, addr, next, nodes,
				    flags, private))
			return -EIO;
	} while (pgd++, addr = next, addr != end);
	return 0;
}
