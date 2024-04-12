__be32 nfsd4_bind_conn_to_session(struct svc_rqst *rqstp,
		     struct nfsd4_compound_state *cstate,
		     struct nfsd4_bind_conn_to_session *bcts)
{
	__be32 status;
	struct nfsd4_conn *conn;
	struct nfsd4_session *session;
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	if (!nfsd4_last_compound_op(rqstp))
		return nfserr_not_only_op;
	spin_lock(&nn->client_lock);
	session = find_in_sessionid_hashtbl(&bcts->sessionid, net, &status);
	spin_unlock(&nn->client_lock);
	if (!session)
		goto out_no_session;
	status = nfserr_wrong_cred;
	if (!nfsd4_mach_creds_match(session->se_client, rqstp))
		goto out;
	status = nfsd4_map_bcts_dir(&bcts->dir);
	if (status)
		goto out;
	conn = alloc_conn(rqstp, bcts->dir);
	status = nfserr_jukebox;
	if (!conn)
		goto out;
	nfsd4_init_conn(rqstp, conn, session);
	status = nfs_ok;
out:
	nfsd4_put_session(session);
out_no_session:
	return status;
}
