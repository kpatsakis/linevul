static bool update_transition_efer(struct vcpu_vmx *vmx, int efer_offset)
{
	u64 guest_efer = vmx->vcpu.arch.efer;
	u64 ignore_bits = 0;

	if (!enable_ept) {
		/*
		 * NX is needed to handle CR0.WP=1, CR4.SMEP=1.  Testing
		 * host CPUID is more efficient than testing guest CPUID
		 * or CR4.  Host SMEP is anyway a requirement for guest SMEP.
		 */
		if (boot_cpu_has(X86_FEATURE_SMEP))
			guest_efer |= EFER_NX;
		else if (!(guest_efer & EFER_NX))
			ignore_bits |= EFER_NX;
	}

	/*
	 * LMA and LME handled by hardware; SCE meaningless outside long mode.
	 */
	ignore_bits |= EFER_SCE;
#ifdef CONFIG_X86_64
	ignore_bits |= EFER_LMA | EFER_LME;
	/* SCE is meaningful only in long mode on Intel */
	if (guest_efer & EFER_LMA)
		ignore_bits &= ~(u64)EFER_SCE;
#endif

	clear_atomic_switch_msr(vmx, MSR_EFER);

	/*
	 * On EPT, we can't emulate NX, so we must switch EFER atomically.
	 * On CPUs that support "load IA32_EFER", always switch EFER
	 * atomically, since it's faster than switching it manually.
	 */
	if (cpu_has_load_ia32_efer ||
	    (enable_ept && ((vmx->vcpu.arch.efer ^ host_efer) & EFER_NX))) {
		if (!(guest_efer & EFER_LMA))
			guest_efer &= ~EFER_LME;
		if (guest_efer != host_efer)
			add_atomic_switch_msr(vmx, MSR_EFER,
					      guest_efer, host_efer);
		return false;
	} else {
		guest_efer &= ~ignore_bits;
		guest_efer |= host_efer & ignore_bits;

		vmx->guest_msrs[efer_offset].data = guest_efer;
		vmx->guest_msrs[efer_offset].mask = ~ignore_bits;

		return true;
	}
}
