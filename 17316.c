static void nfsd4_close_open_stateid(struct nfs4_ol_stateid *s)
{
	struct nfs4_client *clp = s->st_stid.sc_client;
	bool unhashed;
	LIST_HEAD(reaplist);

	s->st_stid.sc_type = NFS4_CLOSED_STID;
	spin_lock(&clp->cl_lock);
	unhashed = unhash_open_stateid(s, &reaplist);

	if (clp->cl_minorversion) {
		if (unhashed)
			put_ol_stateid_locked(s, &reaplist);
		spin_unlock(&clp->cl_lock);
		free_ol_stateid_reaplist(&reaplist);
	} else {
		spin_unlock(&clp->cl_lock);
		free_ol_stateid_reaplist(&reaplist);
		if (unhashed)
			move_to_close_lru(s, clp->net);
	}
}
