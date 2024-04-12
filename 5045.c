static u8 vmx_msr_bitmap_mode(struct kvm_vcpu *vcpu)
{
	u8 mode = 0;

	if (cpu_has_secondary_exec_ctrls() &&
	    (vmcs_read32(SECONDARY_VM_EXEC_CONTROL) &
	     SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE)) {
		mode |= MSR_BITMAP_MODE_X2APIC;
		if (enable_apicv && kvm_vcpu_apicv_active(vcpu))
			mode |= MSR_BITMAP_MODE_X2APIC_APICV;
	}

	if (is_long_mode(vcpu))
		mode |= MSR_BITMAP_MODE_LM;

	return mode;
}
