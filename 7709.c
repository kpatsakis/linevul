static void nfsd4_deleg_xgrade_none_ext(struct nfsd4_open *open,
					struct nfs4_delegation *dp)
{
	if (open->op_deleg_want == NFS4_SHARE_WANT_READ_DELEG &&
	    dp->dl_type == NFS4_OPEN_DELEGATE_WRITE) {
		open->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
		open->op_why_no_deleg = WND4_NOT_SUPP_DOWNGRADE;
	} else if (open->op_deleg_want == NFS4_SHARE_WANT_WRITE_DELEG &&
		   dp->dl_type == NFS4_OPEN_DELEGATE_WRITE) {
		open->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
		open->op_why_no_deleg = WND4_NOT_SUPP_UPGRADE;
	}
	/* Otherwise the client must be confused wanting a delegation
	 * it already has, therefore we don't return
	 * NFS4_OPEN_DELEGATE_NONE_EXT and reason.
	 */
}
