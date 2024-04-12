static int arm_init(void)
{
	int rc = kvm_init(NULL, sizeof(struct kvm_vcpu), 0, THIS_MODULE);
	return rc;
}
