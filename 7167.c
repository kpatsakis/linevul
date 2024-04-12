static void nfs4_free_deleg(struct nfs4_stid *stid)
{
	kmem_cache_free(deleg_slab, stid);
	atomic_long_dec(&num_delegations);
}
