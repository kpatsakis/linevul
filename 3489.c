static bool emulator_get_cpuid(struct x86_emulate_ctxt *ctxt,
			       u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
{
	struct kvm_cpuid_entry2 *cpuid = NULL;

	if (eax && ecx)
		cpuid = kvm_find_cpuid_entry(emul_to_vcpu(ctxt),
					    *eax, *ecx);

	if (cpuid) {
		*eax = cpuid->eax;
		*ecx = cpuid->ecx;
		if (ebx)
			*ebx = cpuid->ebx;
		if (edx)
			*edx = cpuid->edx;
		return true;
	}

	return false;
}
