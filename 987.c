static void encode_lockt(struct xdr_stream *xdr, const struct nfs_lockt_args *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 24);
	*p++ = cpu_to_be32(OP_LOCKT);
	*p++ = cpu_to_be32(nfs4_lock_type(args->fl, 0));
	p = xdr_encode_hyper(p, args->fl->fl_start);
	p = xdr_encode_hyper(p, nfs4_lock_length(args->fl));
	encode_lockowner(xdr, &args->lock_owner);
	hdr->nops++;
	hdr->replen += decode_lockt_maxsz;
}
