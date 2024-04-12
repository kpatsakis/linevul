static uint32_t kvm_get_exit_reason(struct kvm_vcpu *vcpu)
{
	struct exit_ctl_data *p_exit_data;

	p_exit_data = kvm_get_exit_data(vcpu);
	return p_exit_data->exit_reason;
}
