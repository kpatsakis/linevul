find_lock_stateid(struct nfs4_lockowner *lo, struct nfs4_file *fp)
{
	struct nfs4_ol_stateid *lst;
	struct nfs4_client *clp = lo->lo_owner.so_client;

	lockdep_assert_held(&clp->cl_lock);

	list_for_each_entry(lst, &lo->lo_owner.so_stateids, st_perstateowner) {
		if (lst->st_stid.sc_file == fp) {
			atomic_inc(&lst->st_stid.sc_count);
			return lst;
		}
	}
	return NULL;
}
