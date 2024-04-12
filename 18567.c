static bool nested_cr4_valid(struct kvm_vcpu *vcpu, unsigned long val)
{
	u64 fixed0 = to_vmx(vcpu)->nested.msrs.cr4_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msrs.cr4_fixed1;

	return fixed_bits_valid(val, fixed0, fixed1);
}
