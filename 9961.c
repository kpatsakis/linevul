void kvm_define_shared_msr(unsigned slot, u32 msr)
{
	if (slot >= shared_msrs_global.nr)
		shared_msrs_global.nr = slot + 1;
	shared_msrs_global.msrs[slot] = msr;
	/* we need ensured the shared_msr_global have been updated */
	smp_wmb();
}