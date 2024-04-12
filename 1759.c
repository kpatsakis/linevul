void __init native_pv_lock_init(void)
{
	if (!static_cpu_has(X86_FEATURE_HYPERVISOR))
		static_branch_disable(&virt_spin_lock_key);
}
