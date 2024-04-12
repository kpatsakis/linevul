static void revoke_delegation(struct nfs4_delegation *dp)
{
	struct nfs4_client *clp = dp->dl_stid.sc_client;

	WARN_ON(!list_empty(&dp->dl_recall_lru));

	put_clnt_odstate(dp->dl_clnt_odstate);
	nfs4_put_deleg_lease(dp->dl_stid.sc_file);

	if (clp->cl_minorversion == 0)
		nfs4_put_stid(&dp->dl_stid);
	else {
		dp->dl_stid.sc_type = NFS4_REVOKED_DELEG_STID;
		spin_lock(&clp->cl_lock);
		list_add(&dp->dl_recall_lru, &clp->cl_revoked);
		spin_unlock(&clp->cl_lock);
	}
}
