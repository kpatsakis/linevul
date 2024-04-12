static inline bool nested_cpu_has_vmwrite_any_field(struct kvm_vcpu *vcpu)
{
	return to_vmx(vcpu)->nested.msrs.misc_low &
		MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS;
}
