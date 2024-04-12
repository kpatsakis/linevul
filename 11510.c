static void kvm_free_vmm_area(void)
{
	if (kvm_vmm_base) {
		/*Zero this area before free to avoid bits leak!!*/
		memset((void *)kvm_vmm_base, 0, KVM_VMM_SIZE);
		free_pages(kvm_vmm_base, get_order(KVM_VMM_SIZE));
		kvm_vmm_base  = 0;
		kvm_vm_buffer = 0;
		kvm_vsa_base = 0;
	}
}
