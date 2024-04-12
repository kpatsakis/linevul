int __kvm_arm_vcpu_set_events(struct kvm_vcpu *vcpu,
			      struct kvm_vcpu_events *events)
{
	bool serror_pending = events->exception.serror_pending;
	bool has_esr = events->exception.serror_has_esr;

	if (serror_pending && has_esr) {
		if (!cpus_have_const_cap(ARM64_HAS_RAS_EXTN))
			return -EINVAL;

		if (!((events->exception.serror_esr) & ~ESR_ELx_ISS_MASK))
			kvm_set_sei_esr(vcpu, events->exception.serror_esr);
		else
			return -EINVAL;
	} else if (serror_pending) {
		kvm_inject_vabt(vcpu);
	}

	return 0;
}
