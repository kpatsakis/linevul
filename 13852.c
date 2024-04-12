int kvm_arm_vcpu_arch_has_attr(struct kvm_vcpu *vcpu,
			       struct kvm_device_attr *attr)
{
	int ret;

	switch (attr->group) {
	case KVM_ARM_VCPU_PMU_V3_CTRL:
		ret = kvm_arm_pmu_v3_has_attr(vcpu, attr);
		break;
	case KVM_ARM_VCPU_TIMER_CTRL:
		ret = kvm_arm_timer_has_attr(vcpu, attr);
		break;
	default:
		ret = -ENXIO;
		break;
	}

	return ret;
}
