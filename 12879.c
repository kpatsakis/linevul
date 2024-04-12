put_clnt_odstate(struct nfs4_clnt_odstate *co)
{
	struct nfs4_file *fp;

	if (!co)
		return;

	fp = co->co_file;
	if (atomic_dec_and_lock(&co->co_odcount, &fp->fi_lock)) {
		list_del(&co->co_perfile);
		spin_unlock(&fp->fi_lock);

		nfsd4_return_all_file_layouts(co->co_client, fp);
		kmem_cache_free(odstate_slab, co);
	}
}
