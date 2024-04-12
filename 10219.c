static void walk_shadow_page_lockless_end(struct kvm_vcpu *vcpu)
{
	/*
	 * Make sure the write to vcpu->mode is not reordered in front of
	 * reads to sptes.  If it does, kvm_commit_zap_page() can see us
	 * OUTSIDE_GUEST_MODE and proceed to free the shadow page table.
	 */
	smp_mb();
	vcpu->mode = OUTSIDE_GUEST_MODE;
	local_irq_enable();
}
