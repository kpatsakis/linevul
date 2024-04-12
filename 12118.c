nfsd4_decode_layoutreturn(struct nfsd4_compoundargs *argp,
		struct nfsd4_layoutreturn *lrp)
{
	DECODE_HEAD;

	READ_BUF(16);
	lrp->lr_reclaim = be32_to_cpup(p++);
	lrp->lr_layout_type = be32_to_cpup(p++);
	lrp->lr_seg.iomode = be32_to_cpup(p++);
	lrp->lr_return_type = be32_to_cpup(p++);
	if (lrp->lr_return_type == RETURN_FILE) {
		READ_BUF(16);
		p = xdr_decode_hyper(p, &lrp->lr_seg.offset);
		p = xdr_decode_hyper(p, &lrp->lr_seg.length);

		status = nfsd4_decode_stateid(argp, &lrp->lr_sid);
		if (status)
			return status;

		READ_BUF(4);
		lrp->lrf_body_len = be32_to_cpup(p++);
		if (lrp->lrf_body_len > 0) {
			READ_BUF(lrp->lrf_body_len);
			READMEM(lrp->lrf_body, lrp->lrf_body_len);
		}
	} else {
		lrp->lr_seg.offset = 0;
		lrp->lr_seg.length = NFS4_MAX_UINT64;
	}

	DECODE_TAIL;
}
