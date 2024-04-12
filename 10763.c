static int handle_pause(struct kvm_vcpu *vcpu)
{
	if (ple_gap)
		grow_ple_window(vcpu);

	kvm_vcpu_on_spin(vcpu);
	return kvm_skip_emulated_instruction(vcpu);
}
