nfsd4_encode_test_stateid(struct nfsd4_compoundres *resp, __be32 nfserr,
			  struct nfsd4_test_stateid *test_stateid)
{
	struct xdr_stream *xdr = &resp->xdr;
	struct nfsd4_test_stateid_id *stateid, *next;
	__be32 *p;

	if (nfserr)
		return nfserr;

	p = xdr_reserve_space(xdr, 4 + (4 * test_stateid->ts_num_ids));
	if (!p)
		return nfserr_resource;
	*p++ = htonl(test_stateid->ts_num_ids);

	list_for_each_entry_safe(stateid, next, &test_stateid->ts_stateid_list, ts_id_list) {
		*p++ = stateid->ts_id_status;
	}

	return nfserr;
}
