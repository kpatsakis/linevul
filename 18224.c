static bool clp_used_exchangeid(struct nfs4_client *clp)
{
	return clp->cl_exchange_flags != 0;
} 
