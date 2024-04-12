static int rmap_add(struct kvm_vcpu *vcpu, u64 *spte, gfn_t gfn)
{
	struct kvm_mmu_page *sp;
	unsigned long *rmapp;

	sp = page_header(__pa(spte));
	kvm_mmu_page_set_gfn(sp, spte - sp->spt, gfn);
	rmapp = gfn_to_rmap(vcpu->kvm, gfn, sp->role.level);
	return pte_list_add(vcpu, spte, rmapp);
}
