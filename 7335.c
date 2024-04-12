static int vmx_vm_init(struct kvm *kvm)
{
	if (!ple_gap)
		kvm->arch.pause_in_guest = true;
	return 0;
}
