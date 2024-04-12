nfssvc_decode_fhandle(struct svc_rqst *rqstp, __be32 *p, struct nfsd_fhandle *args)
{
	p = decode_fh(p, &args->fh);
	if (!p)
		return 0;
	return xdr_argsize_check(rqstp, p);
}
