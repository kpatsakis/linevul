nfsd4_close(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    struct nfsd4_close *close)
{
	__be32 status;
	struct nfs4_ol_stateid *stp;
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprintk("NFSD: nfsd4_close on file %pd\n", 
			cstate->current_fh.fh_dentry);

	status = nfs4_preprocess_seqid_op(cstate, close->cl_seqid,
					&close->cl_stateid,
					NFS4_OPEN_STID|NFS4_CLOSED_STID,
					&stp, nn);
	nfsd4_bump_seqid(cstate, status);
	if (status)
		goto out; 
	nfs4_inc_and_copy_stateid(&close->cl_stateid, &stp->st_stid);
	mutex_unlock(&stp->st_mutex);

	nfsd4_close_open_stateid(stp);

	/* put reference from nfs4_preprocess_seqid_op */
	nfs4_put_stid(&stp->st_stid);
out:
	return status;
}
