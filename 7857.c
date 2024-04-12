static u64 compute_guest_tsc(struct kvm_vcpu *vcpu, s64 kernel_ns)
{
	u64 tsc = pvclock_scale_delta(kernel_ns-vcpu->arch.last_tsc_nsec,
				      vcpu->kvm->arch.virtual_tsc_mult,
				      vcpu->kvm->arch.virtual_tsc_shift);
	tsc += vcpu->arch.last_tsc_write;
	return tsc;
}
