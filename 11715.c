static void encode_getattr_one(struct xdr_stream *xdr, uint32_t bitmap, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 12);
	*p++ = cpu_to_be32(OP_GETATTR);
	*p++ = cpu_to_be32(1);
	*p = cpu_to_be32(bitmap);
	hdr->nops++;
	hdr->replen += decode_getattr_maxsz;
}
