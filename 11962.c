static int decode_attr_maxfilesize(struct xdr_stream *xdr, uint32_t *bitmap, uint64_t *res)
{
	__be32 *p;
	int status = 0;

	*res = 0;
	if (unlikely(bitmap[0] & (FATTR4_WORD0_MAXFILESIZE - 1U)))
		return -EIO;
	if (likely(bitmap[0] & FATTR4_WORD0_MAXFILESIZE)) {
		p = xdr_inline_decode(xdr, 8);
		if (unlikely(!p))
			goto out_overflow;
		xdr_decode_hyper(p, res);
		bitmap[0] &= ~FATTR4_WORD0_MAXFILESIZE;
	}
	dprintk("%s: maxfilesize=%Lu\n", __func__, (unsigned long long)*res);
	return status;
out_overflow:
	print_overflow_msg(__func__, xdr);
	return -EIO;
}
