free_client(struct nfs4_client *clp)
{
	while (!list_empty(&clp->cl_sessions)) {
		struct nfsd4_session *ses;
		ses = list_entry(clp->cl_sessions.next, struct nfsd4_session,
				se_perclnt);
		list_del(&ses->se_perclnt);
		WARN_ON_ONCE(atomic_read(&ses->se_ref));
		free_session(ses);
	}
	rpc_destroy_wait_queue(&clp->cl_cb_waitq);
	free_svc_cred(&clp->cl_cred);
	kfree(clp->cl_ownerstr_hashtbl);
	kfree(clp->cl_name.data);
	idr_destroy(&clp->cl_stateids);
	kfree(clp);
}
