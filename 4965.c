static void release_lock_stateid(struct nfs4_ol_stateid *stp)
{
	struct nfs4_client *clp = stp->st_stid.sc_client;
	bool unhashed;

	spin_lock(&clp->cl_lock);
	unhashed = unhash_lock_stateid(stp);
	spin_unlock(&clp->cl_lock);
	if (unhashed)
		nfs4_put_stid(&stp->st_stid);
}
