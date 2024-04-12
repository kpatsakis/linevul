int kvm_lapic_find_highest_irr(struct kvm_vcpu *vcpu)
{
	int highest_irr;

	/* This may race with setting of irr in __apic_accept_irq() and
	 * value returned may be wrong, but kvm_vcpu_kick() in __apic_accept_irq
	 * will cause vmexit immediately and the value will be recalculated
	 * on the next vmentry.
	 */
	if (!kvm_vcpu_has_lapic(vcpu))
		return 0;
	highest_irr = apic_find_highest_irr(vcpu->arch.apic);

	return highest_irr;
}
