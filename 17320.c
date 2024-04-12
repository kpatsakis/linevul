nfs4_put_stid(struct nfs4_stid *s)
{
	struct nfs4_file *fp = s->sc_file;
	struct nfs4_client *clp = s->sc_client;

	might_lock(&clp->cl_lock);

	if (!atomic_dec_and_lock(&s->sc_count, &clp->cl_lock)) {
		wake_up_all(&close_wq);
		return;
	}
	idr_remove(&clp->cl_stateids, s->sc_stateid.si_opaque.so_id);
	spin_unlock(&clp->cl_lock);
	s->sc_free(s);
	if (fp)
		put_nfs4_file(fp);
}
