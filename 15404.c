nfs3svc_release_fhandle2(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_fhandle_pair *resp)
{
	fh_put(&resp->fh1);
	fh_put(&resp->fh2);
	return 1;
}
