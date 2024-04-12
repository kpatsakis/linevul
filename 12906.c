static int handle_ept_misconfig(struct kvm_vcpu *vcpu)
{
	gpa_t gpa;

	/*
	 * A nested guest cannot optimize MMIO vmexits, because we have an
	 * nGPA here instead of the required GPA.
	 */
	gpa = vmcs_read64(GUEST_PHYSICAL_ADDRESS);
	if (!is_guest_mode(vcpu) &&
	    !kvm_io_bus_write(vcpu, KVM_FAST_MMIO_BUS, gpa, 0, NULL)) {
		trace_kvm_fast_mmio(gpa);
		/*
		 * Doing kvm_skip_emulated_instruction() depends on undefined
		 * behavior: Intel's manual doesn't mandate
		 * VM_EXIT_INSTRUCTION_LEN to be set in VMCS when EPT MISCONFIG
		 * occurs and while on real hardware it was observed to be set,
		 * other hypervisors (namely Hyper-V) don't set it, we end up
		 * advancing IP with some random value. Disable fast mmio when
		 * running nested and keep it for real hardware in hope that
		 * VM_EXIT_INSTRUCTION_LEN will always be set correctly.
		 */
		if (!static_cpu_has(X86_FEATURE_HYPERVISOR))
			return kvm_skip_emulated_instruction(vcpu);
		else
			return x86_emulate_instruction(vcpu, gpa, EMULTYPE_SKIP,
						       NULL, 0) == EMULATE_DONE;
	}

	return kvm_mmu_page_fault(vcpu, gpa, PFERR_RSVD_MASK, NULL, 0);
}
