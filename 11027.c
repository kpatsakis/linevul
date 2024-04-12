static inline u64 __scale_tsc(u64 ratio, u64 tsc)
{
	return mul_u64_u64_shr(tsc, ratio, kvm_tsc_scaling_ratio_frac_bits);
}
