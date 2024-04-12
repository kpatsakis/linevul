nfsd4_encode_create(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_create *create)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	if (!nfserr) {
		p = xdr_reserve_space(xdr, 20);
		if (!p)
			return nfserr_resource;
		encode_cinfo(p, &create->cr_cinfo);
		nfserr = nfsd4_encode_bitmap(xdr, create->cr_bmval[0],
				create->cr_bmval[1], create->cr_bmval[2]);
	}
	return nfserr;
}
