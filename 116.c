nfs3svc_encode_wccstat(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_attrstat *resp)
{
	p = encode_wcc_data(rqstp, p, &resp->fh);
	return xdr_ressize_check(rqstp, p);
}
