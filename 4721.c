do_translation_fault(unsigned long addr, unsigned int fsr,
		     struct pt_regs *regs)
{
	unsigned int index;
	pgd_t *pgd, *pgd_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	if (addr < TASK_SIZE)
		return do_page_fault(addr, fsr, regs);

	if (user_mode(regs))
		goto bad_area;

	index = pgd_index(addr);

	/*
	 * FIXME: CP15 C1 is write only on ARMv3 architectures.
	 */
	pgd = cpu_get_pgd() + index;
	pgd_k = init_mm.pgd + index;

	if (pgd_none(*pgd_k))
		goto bad_area;
	if (!pgd_present(*pgd))
		set_pgd(pgd, *pgd_k);

	pud = pud_offset(pgd, addr);
	pud_k = pud_offset(pgd_k, addr);

	if (pud_none(*pud_k))
		goto bad_area;
	if (!pud_present(*pud))
		set_pud(pud, *pud_k);

	pmd = pmd_offset(pud, addr);
	pmd_k = pmd_offset(pud_k, addr);

	/*
	 * On ARM one Linux PGD entry contains two hardware entries (see page
	 * tables layout in pgtable.h). We normally guarantee that we always
	 * fill both L1 entries. But create_mapping() doesn't follow the rule.
	 * It can create inidividual L1 entries, so here we have to call
	 * pmd_none() check for the entry really corresponded to address, not
	 * for the first of pair.
	 */
	index = (addr >> SECTION_SHIFT) & 1;
	if (pmd_none(pmd_k[index]))
		goto bad_area;

	copy_pmd(pmd, pmd_k);
	return 0;

bad_area:
	do_bad_area(addr, fsr, regs);
	return 0;
}
