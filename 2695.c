void nfsd4_bump_seqid(struct nfsd4_compound_state *cstate, __be32 nfserr)
{
	struct nfs4_stateowner *so = cstate->replay_owner;

	if (nfserr == nfserr_replay_me)
		return;

	if (!seqid_mutating_err(ntohl(nfserr))) {
		nfsd4_cstate_clear_replay(cstate);
		return;
	}
	if (!so)
		return;
	if (so->so_is_open_owner)
		release_last_closed_stateid(openowner(so));
	so->so_seqid++;
	return;
}
