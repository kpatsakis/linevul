static void kvm_gen_kvmclock_update(struct kvm_vcpu *v)
{
	int i;
	struct kvm *kvm = v->kvm;
	struct kvm_vcpu *vcpu;

	kvm_for_each_vcpu(i, vcpu, kvm) {
		set_bit(KVM_REQ_CLOCK_UPDATE, &vcpu->requests);
		kvm_vcpu_kick(vcpu);
	}
}
