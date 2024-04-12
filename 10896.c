static void flush_tlb_func(void *info)
{
	struct flush_tlb_info *f = info;

	inc_irq_stat(irq_tlb_count);

	if (f->flush_mm != this_cpu_read(cpu_tlbstate.active_mm))
		return;
	if (!f->flush_end)
		f->flush_end = f->flush_start + PAGE_SIZE;

	count_vm_tlb_event(NR_TLB_REMOTE_FLUSH_RECEIVED);
	if (this_cpu_read(cpu_tlbstate.state) == TLBSTATE_OK) {
		if (f->flush_end == TLB_FLUSH_ALL) {
			local_flush_tlb();
			trace_tlb_flush(TLB_REMOTE_SHOOTDOWN, TLB_FLUSH_ALL);
		} else {
			unsigned long addr;
			unsigned long nr_pages =
				(f->flush_end - f->flush_start) / PAGE_SIZE;
			addr = f->flush_start;
			while (addr < f->flush_end) {
				__flush_tlb_single(addr);
				addr += PAGE_SIZE;
			}
			trace_tlb_flush(TLB_REMOTE_SHOOTDOWN, nr_pages);
		}
	} else
		leave_mm(smp_processor_id());

}
