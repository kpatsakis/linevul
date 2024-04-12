static int apic_mmio_in_range(struct kvm_lapic *apic, gpa_t addr)
{
	return kvm_apic_hw_enabled(apic) &&
	    addr >= apic->base_address &&
	    addr < apic->base_address + LAPIC_MMIO_LENGTH;
}
