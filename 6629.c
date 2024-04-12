static __be32 get_client_locked(struct nfs4_client *clp)
{
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_assert_held(&nn->client_lock);

	if (is_client_expired(clp))
		return nfserr_expired;
	atomic_inc(&clp->cl_refcount);
	return nfs_ok;
}
