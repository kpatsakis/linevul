nfssvc_decode_createargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd_createargs *args)
{
	if (   !(p = decode_fh(p, &args->fh))
	    || !(p = decode_filename(p, &args->name, &args->len)))
		return 0;
	p = decode_sattr(p, &args->attrs);

	return xdr_argsize_check(rqstp, p);
}
