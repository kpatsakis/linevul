static bool nested_host_cr0_valid(struct kvm_vcpu *vcpu, unsigned long val)
{
	u64 fixed0 = to_vmx(vcpu)->nested.nested_vmx_cr0_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.nested_vmx_cr0_fixed1;

	return fixed_bits_valid(val, fixed0, fixed1);
}
