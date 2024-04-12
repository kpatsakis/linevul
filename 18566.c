find_blocked_lock(struct nfs4_lockowner *lo, struct knfsd_fh *fh,
			struct nfsd_net *nn)
{
	struct nfsd4_blocked_lock *cur, *found = NULL;

	spin_lock(&nn->blocked_locks_lock);
	list_for_each_entry(cur, &lo->lo_blocked, nbl_list) {
		if (fh_match(fh, &cur->nbl_fh)) {
			list_del_init(&cur->nbl_list);
			list_del_init(&cur->nbl_lru);
			found = cur;
			break;
		}
	}
	spin_unlock(&nn->blocked_locks_lock);
	if (found)
		posix_unblock_lock(&found->nbl_lock);
	return found;
}
