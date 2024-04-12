static int ip6mr_mfc_delete(struct mr6_table *mrt, struct mf6cctl *mfc,
			    int parent)
{
	int line;
	struct mfc6_cache *c, *next;

	line = MFC6_HASH(&mfc->mf6cc_mcastgrp.sin6_addr, &mfc->mf6cc_origin.sin6_addr);

	list_for_each_entry_safe(c, next, &mrt->mfc6_cache_array[line], list) {
		if (ipv6_addr_equal(&c->mf6c_origin, &mfc->mf6cc_origin.sin6_addr) &&
		    ipv6_addr_equal(&c->mf6c_mcastgrp,
				    &mfc->mf6cc_mcastgrp.sin6_addr) &&
		    (parent == -1 || parent == c->mf6c_parent)) {
			write_lock_bh(&mrt_lock);
			list_del(&c->list);
			write_unlock_bh(&mrt_lock);

			mr6_netlink_event(mrt, c, RTM_DELROUTE);
			ip6mr_cache_free(c);
			return 0;
		}
	}
	return -ENOENT;
}
