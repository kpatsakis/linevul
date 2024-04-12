nfsd4_encode_open_downgrade(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_open_downgrade *od)
{
	struct xdr_stream *xdr = &resp->xdr;

	if (!nfserr)
		nfserr = nfsd4_encode_stateid(xdr, &od->od_stateid);

	return nfserr;
}
