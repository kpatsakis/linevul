static int kvm_iommu_map_memslots(struct kvm *kvm)
{
	int idx, r = 0;
	struct kvm_memslots *slots;
	struct kvm_memory_slot *memslot;

	idx = srcu_read_lock(&kvm->srcu);
	slots = kvm_memslots(kvm);

	kvm_for_each_memslot(memslot, slots) {
		r = kvm_iommu_map_pages(kvm, memslot);
		if (r)
			break;
	}
	srcu_read_unlock(&kvm->srcu, idx);

	return r;
}
