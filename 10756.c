get_clnt_odstate(struct nfs4_clnt_odstate *co)
{
	if (co)
		atomic_inc(&co->co_odcount);
}
