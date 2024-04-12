exp_build_l4proto_sctp(const struct nf_conntrack *ct, struct nethdr *n, int a)
{
	ct_build_group(ct, ATTR_GRP_ORIG_PORT, n, a,
			sizeof(struct nfct_attr_grp_port));
}
