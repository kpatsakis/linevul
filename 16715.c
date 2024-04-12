void kvm_arch_memslots_updated(struct kvm *kvm, struct kvm_memslots *slots)
{
	/*
	 * memslots->generation has been incremented.
	 * mmio generation may have reached its maximum value.
	 */
	kvm_mmu_invalidate_mmio_sptes(kvm, slots);
}
