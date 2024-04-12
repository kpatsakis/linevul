access_permit_write(struct nfs4_ol_stateid *stp)
{
	return test_access(NFS4_SHARE_ACCESS_WRITE, stp) ||
		test_access(NFS4_SHARE_ACCESS_BOTH, stp);
}
