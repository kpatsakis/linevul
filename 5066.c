struct kvm_vcpu __percpu **kvm_get_running_vcpus(void)
{
	return &kvm_arm_running_vcpu;
}
