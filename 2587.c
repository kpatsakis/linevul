nfssvc_encode_attrstat(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd_attrstat *resp)
{
	p = encode_fattr(rqstp, p, &resp->fh, &resp->stat);
	return xdr_ressize_check(rqstp, p);
}
