void kvm_apic_write_nodecode(struct kvm_vcpu *vcpu, u32 offset)
{
	u32 val = 0;

	/* hw has done the conditional check and inst decode */
	offset &= 0xff0;

	apic_reg_read(vcpu->arch.apic, offset, 4, &val);

	/* TODO: optimize to just emulate side effect w/o one more write */
	apic_reg_write(vcpu->arch.apic, offset, val);
}
