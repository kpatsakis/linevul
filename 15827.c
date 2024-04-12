static struct kvm_memslots *kvm_alloc_memslots(void)
{
	int i;
	struct kvm_memslots *slots;

	slots = kvm_kvzalloc(sizeof(struct kvm_memslots));
	if (!slots)
		return NULL;

	/*
	 * Init kvm generation close to the maximum to easily test the
	 * code of handling generation number wrap-around.
	 */
	slots->generation = -150;
	for (i = 0; i < KVM_MEM_SLOTS_NUM; i++)
		slots->id_to_index[i] = slots->memslots[i].id = i;

	return slots;
}
