static inline int vmcs12_write_any(struct kvm_vcpu *vcpu,
				   unsigned long field, u64 field_value){
	short offset = vmcs_field_to_offset(field);
	char *p = ((char *) get_vmcs12(vcpu)) + offset;
	if (offset < 0)
		return offset;

	switch (vmcs_field_width(field)) {
	case VMCS_FIELD_WIDTH_U16:
		*(u16 *)p = field_value;
		return 0;
	case VMCS_FIELD_WIDTH_U32:
		*(u32 *)p = field_value;
		return 0;
	case VMCS_FIELD_WIDTH_U64:
		*(u64 *)p = field_value;
		return 0;
	case VMCS_FIELD_WIDTH_NATURAL_WIDTH:
		*(natural_width *)p = field_value;
		return 0;
	default:
		WARN_ON(1);
		return -ENOENT;
	}

}
