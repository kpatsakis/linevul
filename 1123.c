void ct2msg(const struct nf_conntrack *ct, struct nethdr *n)
{
	uint8_t l4proto = nfct_get_attr_u8(ct, ATTR_L4PROTO);

	if (nfct_attr_grp_is_set(ct, ATTR_GRP_ORIG_IPV4)) {
		ct_build_group(ct, ATTR_GRP_ORIG_IPV4, n, NTA_IPV4, 
			      sizeof(struct nfct_attr_grp_ipv4));
	} else if (nfct_attr_grp_is_set(ct, ATTR_GRP_ORIG_IPV6)) {
		ct_build_group(ct, ATTR_GRP_ORIG_IPV6, n, NTA_IPV6, 
			      sizeof(struct nfct_attr_grp_ipv6));
	}

	ct_build_u32(ct, ATTR_STATUS, n, NTA_STATUS); 
	ct_build_u8(ct, ATTR_L4PROTO, n, NTA_L4PROTO);

	if (l4proto_fcn[l4proto].build)
		l4proto_fcn[l4proto].build(ct, n);

	if (!CONFIG(commit_timeout) && nfct_attr_is_set(ct, ATTR_TIMEOUT))
		ct_build_u32(ct, ATTR_TIMEOUT, n, NTA_TIMEOUT);
	if (nfct_attr_is_set(ct, ATTR_MARK))
		ct_build_u32(ct, ATTR_MARK, n, NTA_MARK);

	/* setup the master conntrack */
	if (nfct_attr_grp_is_set(ct, ATTR_GRP_MASTER_IPV4)) {
		ct_build_group(ct, ATTR_GRP_MASTER_IPV4, n, NTA_MASTER_IPV4,
			      sizeof(struct nfct_attr_grp_ipv4));
		ct_build_u8(ct, ATTR_MASTER_L4PROTO, n, NTA_MASTER_L4PROTO);
		if (nfct_attr_grp_is_set(ct, ATTR_GRP_MASTER_PORT)) {
			ct_build_group(ct, ATTR_GRP_MASTER_PORT,
				      n, NTA_MASTER_PORT, 
				      sizeof(struct nfct_attr_grp_port));
		}
	} else if (nfct_attr_grp_is_set(ct, ATTR_GRP_MASTER_IPV6)) {
		ct_build_group(ct, ATTR_GRP_MASTER_IPV6, n, NTA_MASTER_IPV6,
			      sizeof(struct nfct_attr_grp_ipv6));
		ct_build_u8(ct, ATTR_MASTER_L4PROTO, n, NTA_MASTER_L4PROTO);
		if (nfct_attr_grp_is_set(ct, ATTR_GRP_MASTER_PORT)) {
			ct_build_group(ct, ATTR_GRP_MASTER_PORT,
				      n, NTA_MASTER_PORT,
				      sizeof(struct nfct_attr_grp_port));
		}
	}

	/*  NAT */
	if (nfct_getobjopt(ct, NFCT_GOPT_IS_SNAT))
		ct_build_u32(ct, ATTR_REPL_IPV4_DST, n, NTA_SNAT_IPV4);
	if (nfct_getobjopt(ct, NFCT_GOPT_IS_DNAT))
		ct_build_u32(ct, ATTR_REPL_IPV4_SRC, n, NTA_DNAT_IPV4);
	if (nfct_getobjopt(ct, NFCT_GOPT_IS_SPAT))
		ct_build_u16(ct, ATTR_REPL_PORT_DST, n, NTA_SPAT_PORT);
	if (nfct_getobjopt(ct, NFCT_GOPT_IS_DPAT))
		ct_build_u16(ct, ATTR_REPL_PORT_SRC, n, NTA_DPAT_PORT);

	/* NAT sequence adjustment */
	if (nfct_attr_is_set_array(ct, nat_type, 6))
		ct_build_natseqadj(ct, n);

	if (nfct_attr_is_set(ct, ATTR_HELPER_NAME))
		ct_build_str(ct, ATTR_HELPER_NAME, n, NTA_HELPER_NAME);

	if (nfct_attr_is_set(ct, ATTR_CONNLABELS))
		ct_build_clabel(ct, n);
}
