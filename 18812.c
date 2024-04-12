nfsd4_delegreturn(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		  struct nfsd4_delegreturn *dr)
{
	struct nfs4_delegation *dp;
	stateid_t *stateid = &dr->dr_stateid;
	struct nfs4_stid *s;
	__be32 status;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	if ((status = fh_verify(rqstp, &cstate->current_fh, S_IFREG, 0)))
		return status;

	status = nfsd4_lookup_stateid(cstate, stateid, NFS4_DELEG_STID, &s, nn);
	if (status)
		goto out;
	dp = delegstateid(s);
	status = check_stateid_generation(stateid, &dp->dl_stid.sc_stateid, nfsd4_has_session(cstate));
	if (status)
		goto put_stateid;

	destroy_delegation(dp);
put_stateid:
	nfs4_put_stid(&dp->dl_stid);
out:
	return status;
}
