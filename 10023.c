static struct sock *llc_lookup_dgram(struct llc_sap *sap,
				     const struct llc_addr *laddr)
{
	struct sock *rc;
	struct hlist_nulls_node *node;
	int slot = llc_sk_laddr_hashfn(sap, laddr);
	struct hlist_nulls_head *laddr_hb = &sap->sk_laddr_hash[slot];

	rcu_read_lock_bh();
again:
	sk_nulls_for_each_rcu(rc, node, laddr_hb) {
		if (llc_dgram_match(sap, laddr, rc)) {
			/* Extra checks required by SLAB_DESTROY_BY_RCU */
			if (unlikely(!atomic_inc_not_zero(&rc->sk_refcnt)))
				goto again;
			if (unlikely(llc_sk(rc)->sap != sap ||
				     !llc_dgram_match(sap, laddr, rc))) {
				sock_put(rc);
				continue;
			}
			goto found;
		}
	}
	rc = NULL;
	/*
	 * if the nulls value we got at the end of this lookup is
	 * not the expected one, we must restart lookup.
	 * We probably met an item that was moved to another chain.
	 */
	if (unlikely(get_nulls_value(node) != slot))
		goto again;
found:
	rcu_read_unlock_bh();
	return rc;
}
