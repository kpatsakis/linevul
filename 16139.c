static int nfs4_wait_clnt_recover(struct nfs_client *clp)
{
	int res;

	might_sleep();

	res = wait_on_bit(&clp->cl_state, NFS4CLNT_MANAGER_RUNNING,
			nfs4_wait_bit_killable, TASK_KILLABLE);
	return res;
}
