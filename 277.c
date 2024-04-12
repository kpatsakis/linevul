static void put_ol_stateid_locked(struct nfs4_ol_stateid *stp,
				       struct list_head *reaplist)
{
	struct nfs4_stid *s = &stp->st_stid;
	struct nfs4_client *clp = s->sc_client;

	lockdep_assert_held(&clp->cl_lock);

	WARN_ON_ONCE(!list_empty(&stp->st_locks));

	if (!atomic_dec_and_test(&s->sc_count)) {
		wake_up_all(&close_wq);
		return;
	}

	idr_remove(&clp->cl_stateids, s->sc_stateid.si_opaque.so_id);
	list_add(&stp->st_locks, reaplist);
}
