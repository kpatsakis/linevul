static int handle_desc(struct kvm_vcpu *vcpu)
{
	WARN_ON(!(vcpu->arch.cr4 & X86_CR4_UMIP));
	return emulate_instruction(vcpu, 0) == EMULATE_DONE;
}
