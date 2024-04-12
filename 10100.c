static bool nested_guest_cr0_valid(struct kvm_vcpu *vcpu, unsigned long val)
{
	u64 fixed0 = to_vmx(vcpu)->nested.msrs.cr0_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msrs.cr0_fixed1;
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);

	if (to_vmx(vcpu)->nested.msrs.secondary_ctls_high &
		SECONDARY_EXEC_UNRESTRICTED_GUEST &&
	    nested_cpu_has2(vmcs12, SECONDARY_EXEC_UNRESTRICTED_GUEST))
		fixed0 &= ~(X86_CR0_PE | X86_CR0_PG);

	return fixed_bits_valid(val, fixed0, fixed1);
}
