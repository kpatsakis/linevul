void kvm_arch_register_noncoherent_dma(struct kvm *kvm)
{
	atomic_inc(&kvm->arch.noncoherent_dma_count);
}
