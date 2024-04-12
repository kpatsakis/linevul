static void kvm_init_tsc_catchup(struct kvm_vcpu *vcpu, u32 this_tsc_khz)
{
	/* Compute a scale to convert nanoseconds in TSC cycles */
	kvm_get_time_scale(this_tsc_khz, NSEC_PER_SEC / 1000,
			   &vcpu->arch.tsc_catchup_shift,
			   &vcpu->arch.tsc_catchup_mult);
}
