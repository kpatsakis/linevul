struct zonelist *huge_zonelist(struct vm_area_struct *vma, unsigned long addr,
				gfp_t gfp_flags, struct mempolicy **mpol,
				nodemask_t **nodemask)
{
	struct zonelist *zl;

	*mpol = get_vma_policy(vma, addr);
	*nodemask = NULL;	/* assume !MPOL_BIND */

	if (unlikely((*mpol)->mode == MPOL_INTERLEAVE)) {
		zl = node_zonelist(interleave_nid(*mpol, vma, addr,
				huge_page_shift(hstate_vma(vma))), gfp_flags);
	} else {
		zl = policy_zonelist(gfp_flags, *mpol, numa_node_id());
		if ((*mpol)->mode == MPOL_BIND)
			*nodemask = &(*mpol)->v.nodes;
	}
	return zl;
}
