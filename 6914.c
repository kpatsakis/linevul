static int decode_compound_hdr(struct xdr_stream *xdr, struct compound_hdr *hdr)
{
	__be32 *p;

	READ_BUF(8);
	READ32(hdr->status);
	READ32(hdr->taglen);
	
	READ_BUF(hdr->taglen + 4);
	hdr->tag = (char *)p;
	p += XDR_QUADLEN(hdr->taglen);
	READ32(hdr->nops);
	return 0;
}
