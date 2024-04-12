nfs3svc_decode_mkdirargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_createargs *args)
{
	if (!(p = decode_fh(p, &args->fh)) ||
	    !(p = decode_filename(p, &args->name, &args->len)))
		return 0;
	p = decode_sattr3(p, &args->attrs);

	return xdr_argsize_check(rqstp, p);
}
