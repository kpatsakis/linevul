static void unhash_lockowner_locked(struct nfs4_lockowner *lo)
{
	struct nfs4_client *clp = lo->lo_owner.so_client;

	lockdep_assert_held(&clp->cl_lock);

	list_del_init(&lo->lo_owner.so_strhash);
}
