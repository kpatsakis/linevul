init_open_stateid(struct nfs4_file *fp, struct nfsd4_open *open)
{

	struct nfs4_openowner *oo = open->op_openowner;
	struct nfs4_ol_stateid *retstp = NULL;
	struct nfs4_ol_stateid *stp;

	stp = open->op_stp;
	/* We are moving these outside of the spinlocks to avoid the warnings */
	mutex_init(&stp->st_mutex);
	mutex_lock(&stp->st_mutex);

	spin_lock(&oo->oo_owner.so_client->cl_lock);
	spin_lock(&fp->fi_lock);

	retstp = nfsd4_find_existing_open(fp, open);
	if (retstp)
		goto out_unlock;

	open->op_stp = NULL;
	atomic_inc(&stp->st_stid.sc_count);
	stp->st_stid.sc_type = NFS4_OPEN_STID;
	INIT_LIST_HEAD(&stp->st_locks);
	stp->st_stateowner = nfs4_get_stateowner(&oo->oo_owner);
	get_nfs4_file(fp);
	stp->st_stid.sc_file = fp;
	stp->st_access_bmap = 0;
	stp->st_deny_bmap = 0;
	stp->st_openstp = NULL;
	list_add(&stp->st_perstateowner, &oo->oo_owner.so_stateids);
	list_add(&stp->st_perfile, &fp->fi_stateids);

out_unlock:
	spin_unlock(&fp->fi_lock);
	spin_unlock(&oo->oo_owner.so_client->cl_lock);
	if (retstp) {
		mutex_lock(&retstp->st_mutex);
		/* To keep mutex tracking happy */
		mutex_unlock(&stp->st_mutex);
		stp = retstp;
	}
	return stp;
}
