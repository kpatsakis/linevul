nfsd_forget_delegations(struct list_head *reaplist)
{
	struct nfs4_client *clp;
	struct nfs4_delegation *dp, *next;

	list_for_each_entry_safe(dp, next, reaplist, dl_recall_lru) {
		list_del_init(&dp->dl_recall_lru);
		clp = dp->dl_stid.sc_client;
		revoke_delegation(dp);
		put_client(clp);
	}
}
