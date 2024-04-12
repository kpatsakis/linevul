find_unconfirmed_client(clientid_t *clid, bool sessions, struct nfsd_net *nn)
{
	struct list_head *tbl = nn->unconf_id_hashtbl;

	lockdep_assert_held(&nn->client_lock);
	return find_client_in_id_table(tbl, clid, sessions);
}
