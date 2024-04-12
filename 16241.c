int kvm_highest_pending_irq(struct kvm_vcpu *vcpu)
{
    struct vpd *vpd = to_host(vcpu->kvm, vcpu->arch.vpd);

    if (vpd->irr[0] & (1UL << NMI_VECTOR))
		return NMI_VECTOR;
    if (vpd->irr[0] & (1UL << ExtINT_VECTOR))
		return ExtINT_VECTOR;

    return find_highest_bits((int *)&vpd->irr[0]);
}
