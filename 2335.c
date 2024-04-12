static struct inet_peer *lookup_rcu(const struct inetpeer_addr *daddr,
				    struct inet_peer_base *base)
{
	struct inet_peer *u = rcu_dereference(base->root);
	int count = 0;

	while (u != peer_avl_empty) {
		int cmp = addr_compare(daddr, &u->daddr);
		if (cmp == 0) {
			/* Before taking a reference, check if this entry was
			 * deleted (refcnt=-1)
			 */
			if (!atomic_add_unless(&u->refcnt, 1, -1))
				u = NULL;
			return u;
		}
		if (cmp == -1)
			u = rcu_dereference(u->avl_left);
		else
			u = rcu_dereference(u->avl_right);
		if (unlikely(++count == PEER_MAXDEPTH))
			break;
	}
	return NULL;
}
