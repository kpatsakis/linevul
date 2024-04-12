nfsd4_get_opendowngradestateid(struct nfsd4_compound_state *cstate, struct nfsd4_open_downgrade *odp)
{
	get_stateid(cstate, &odp->od_stateid);
}
