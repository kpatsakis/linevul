int tcp_md5_do_add(struct sock *sk, const union tcp_md5_addr *addr,
		   int family, const u8 *newkey, u8 newkeylen, gfp_t gfp)
{
	/* Add Key to the list */
	struct tcp_md5sig_key *key;
	struct tcp_sock *tp = tcp_sk(sk);
	struct tcp_md5sig_info *md5sig;

	key = tcp_md5_do_lookup(sk, addr, family);
	if (key) {
		/* Pre-existing entry - just update that one. */
		memcpy(key->key, newkey, newkeylen);
		key->keylen = newkeylen;
		return 0;
	}

	md5sig = rcu_dereference_protected(tp->md5sig_info,
					   lockdep_sock_is_held(sk));
	if (!md5sig) {
		md5sig = kmalloc(sizeof(*md5sig), gfp);
		if (!md5sig)
			return -ENOMEM;

		sk_nocaps_add(sk, NETIF_F_GSO_MASK);
		INIT_HLIST_HEAD(&md5sig->head);
		rcu_assign_pointer(tp->md5sig_info, md5sig);
	}

	key = sock_kmalloc(sk, sizeof(*key), gfp);
	if (!key)
		return -ENOMEM;
	if (!tcp_alloc_md5sig_pool()) {
		sock_kfree_s(sk, key, sizeof(*key));
		return -ENOMEM;
	}

	memcpy(key->key, newkey, newkeylen);
	key->keylen = newkeylen;
	key->family = family;
	memcpy(&key->addr, addr,
	       (family == AF_INET6) ? sizeof(struct in6_addr) :
				      sizeof(struct in_addr));
	hlist_add_head_rcu(&key->node, &md5sig->head);
	return 0;
}
