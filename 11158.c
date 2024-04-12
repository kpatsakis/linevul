void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			   unsigned long end)
{
	unsigned long flags;
	unsigned long long match, pteh=0, pteh_epn, pteh_low;
	unsigned long tlb;
	unsigned int cpu = smp_processor_id();
	struct mm_struct *mm;

	mm = vma->vm_mm;
	if (cpu_context(cpu, mm) == NO_CONTEXT)
		return;

	local_irq_save(flags);

	start &= PAGE_MASK;
	end &= PAGE_MASK;

	match = (cpu_asid(cpu, mm) << PTEH_ASID_SHIFT) | PTEH_VALID;

	/* Flush ITLB */
	for_each_itlb_entry(tlb) {
		asm volatile ("getcfg	%1, 0, %0"
			      : "=r" (pteh)
			      : "r" (tlb) );

		pteh_epn = pteh & PAGE_MASK;
		pteh_low = pteh & ~PAGE_MASK;

		if (pteh_low == match && pteh_epn >= start && pteh_epn <= end)
			__flush_tlb_slot(tlb);
	}

	/* Flush DTLB */
	for_each_dtlb_entry(tlb) {
		asm volatile ("getcfg	%1, 0, %0"
			      : "=r" (pteh)
			      : "r" (tlb) );

		pteh_epn = pteh & PAGE_MASK;
		pteh_low = pteh & ~PAGE_MASK;

		if (pteh_low == match && pteh_epn >= start && pteh_epn <= end)
			__flush_tlb_slot(tlb);
	}

	local_irq_restore(flags);
}
