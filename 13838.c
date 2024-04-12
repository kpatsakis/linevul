static void link_shadow_page(u64 *sptep, struct kvm_mmu_page *sp, bool accessed)
{
	u64 spte;

	BUILD_BUG_ON(VMX_EPT_READABLE_MASK != PT_PRESENT_MASK ||
			VMX_EPT_WRITABLE_MASK != PT_WRITABLE_MASK);

	spte = __pa(sp->spt) | PT_PRESENT_MASK | PT_WRITABLE_MASK |
	       shadow_user_mask | shadow_x_mask;

	if (accessed)
		spte |= shadow_accessed_mask;

	mmu_spte_set(sptep, spte);
}
