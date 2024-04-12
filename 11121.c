nfsd4_open_confirm(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		   struct nfsd4_open_confirm *oc)
{
	__be32 status;
	struct nfs4_openowner *oo;
	struct nfs4_ol_stateid *stp;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	dprintk("NFSD: nfsd4_open_confirm on file %pd\n",
			cstate->current_fh.fh_dentry);

	status = fh_verify(rqstp, &cstate->current_fh, S_IFREG, 0);
	if (status)
		return status;

	status = nfs4_preprocess_seqid_op(cstate,
					oc->oc_seqid, &oc->oc_req_stateid,
					NFS4_OPEN_STID, &stp, nn);
	if (status)
		goto out;
	oo = openowner(stp->st_stateowner);
	status = nfserr_bad_stateid;
	if (oo->oo_flags & NFS4_OO_CONFIRMED) {
		mutex_unlock(&stp->st_mutex);
		goto put_stateid;
	}
	oo->oo_flags |= NFS4_OO_CONFIRMED;
	nfs4_inc_and_copy_stateid(&oc->oc_resp_stateid, &stp->st_stid);
	mutex_unlock(&stp->st_mutex);
	dprintk("NFSD: %s: success, seqid=%d stateid=" STATEID_FMT "\n",
		__func__, oc->oc_seqid, STATEID_VAL(&stp->st_stid.sc_stateid));

	nfsd4_client_record_create(oo->oo_owner.so_client);
	status = nfs_ok;
put_stateid:
	nfs4_put_stid(&stp->st_stid);
out:
	nfsd4_bump_seqid(cstate, status);
	return status;
}
