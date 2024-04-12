static inline void nfs4_stateid_downgrade_bit(struct nfs4_ol_stateid *stp, u32 access)
{
	if (!test_access(access, stp))
		return;
	nfs4_file_put_access(stp->st_stid.sc_file, access);
	clear_access(access, stp);
}
