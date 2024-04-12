static void __always_inline vmx_set_intercept_for_msr(unsigned long *msr_bitmap,
			     			      u32 msr, int type, bool value)
{
	if (value)
		vmx_enable_intercept_for_msr(msr_bitmap, msr, type);
	else
		vmx_disable_intercept_for_msr(msr_bitmap, msr, type);
}
