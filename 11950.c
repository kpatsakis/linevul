static void encode_commit(struct xdr_stream *xdr, const struct nfs_writeargs *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 16);
	*p++ = cpu_to_be32(OP_COMMIT);
	p = xdr_encode_hyper(p, args->offset);
	*p = cpu_to_be32(args->count);
	hdr->nops++;
	hdr->replen += decode_commit_maxsz;
}
