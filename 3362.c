static __be32 *xdr_check_read_list(__be32 *p, __be32 *end)
{
	__be32 *next;

	while (*p++ != xdr_zero) {
		next = p + rpcrdma_readchunk_maxsz - 1;
		if (next > end)
			return NULL;
		p = next;
	}
	return p;
}
