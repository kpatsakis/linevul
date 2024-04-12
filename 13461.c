void kvm_free_pit(struct kvm *kvm)
{
	struct hrtimer *timer;

	if (kvm->arch.vpit) {
		kvm_unregister_irq_mask_notifier(kvm, 0,
					       &kvm->arch.vpit->mask_notifier);
		kvm_unregister_irq_ack_notifier(kvm,
				&kvm->arch.vpit->pit_state.irq_ack_notifier);
		mutex_lock(&kvm->arch.vpit->pit_state.lock);
		timer = &kvm->arch.vpit->pit_state.pit_timer.timer;
		hrtimer_cancel(timer);
		kvm_free_irq_source_id(kvm, kvm->arch.vpit->irq_source_id);
		mutex_unlock(&kvm->arch.vpit->pit_state.lock);
		kfree(kvm->arch.vpit);
	}
}
