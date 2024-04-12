static void rpc_unregister_client(struct rpc_clnt *clnt)
{
	spin_lock(&rpc_client_lock);
	list_del(&clnt->cl_clients);
	spin_unlock(&rpc_client_lock);
}
