nfsd4_get_closestateid(struct nfsd4_compound_state *cstate, struct nfsd4_close *close)
{
	get_stateid(cstate, &close->cl_stateid);
}
