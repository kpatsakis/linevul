void nfsd4_cstate_clear_replay(struct nfsd4_compound_state *cstate)
{
	struct nfs4_stateowner *so = cstate->replay_owner;

	if (so != NULL) {
		cstate->replay_owner = NULL;
		mutex_unlock(&so->so_replay.rp_mutex);
		nfs4_put_stateowner(so);
	}
}
