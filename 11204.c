static bool vendor_intel(struct x86_emulate_ctxt *ctxt)
{
	u32 eax, ebx, ecx, edx;

	eax = ecx = 0;
	ctxt->ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx);
	return ebx == X86EMUL_CPUID_VENDOR_GenuineIntel_ebx
		&& ecx == X86EMUL_CPUID_VENDOR_GenuineIntel_ecx
		&& edx == X86EMUL_CPUID_VENDOR_GenuineIntel_edx;
}
