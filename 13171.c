static int kvm_handle_exit(struct kvm_run *kvm_run, struct kvm_vcpu *vcpu)
{
	u32 exit_reason = kvm_get_exit_reason(vcpu);
	vcpu->arch.last_exit = exit_reason;

	if (exit_reason < kvm_vti_max_exit_handlers
			&& kvm_vti_exit_handlers[exit_reason])
		return kvm_vti_exit_handlers[exit_reason](vcpu, kvm_run);
	else {
		kvm_run->exit_reason = KVM_EXIT_UNKNOWN;
		kvm_run->hw.hardware_exit_reason = exit_reason;
	}
	return 0;
}
