int tcp_v4_md5_do_add(struct sock *sk, __be32 addr,
		      u8 *newkey, u8 newkeylen)
{
	/* Add Key to the list */
	struct tcp_md5sig_key *key;
	struct tcp_sock *tp = tcp_sk(sk);
	struct tcp4_md5sig_key *keys;

	key = tcp_v4_md5_do_lookup(sk, addr);
	if (key) {
		/* Pre-existing entry - just update that one. */
		kfree(key->key);
		key->key = newkey;
		key->keylen = newkeylen;
	} else {
		struct tcp_md5sig_info *md5sig;

		if (!tp->md5sig_info) {
			tp->md5sig_info = kzalloc(sizeof(*tp->md5sig_info),
						  GFP_ATOMIC);
			if (!tp->md5sig_info) {
				kfree(newkey);
				return -ENOMEM;
			}
			sk_nocaps_add(sk, NETIF_F_GSO_MASK);
		}
		if (tcp_alloc_md5sig_pool(sk) == NULL) {
			kfree(newkey);
			return -ENOMEM;
		}
		md5sig = tp->md5sig_info;

		if (md5sig->alloced4 == md5sig->entries4) {
			keys = kmalloc((sizeof(*keys) *
					(md5sig->entries4 + 1)), GFP_ATOMIC);
			if (!keys) {
				kfree(newkey);
				tcp_free_md5sig_pool();
				return -ENOMEM;
			}

			if (md5sig->entries4)
				memcpy(keys, md5sig->keys4,
				       sizeof(*keys) * md5sig->entries4);

			/* Free old key list, and reference new one */
			kfree(md5sig->keys4);
			md5sig->keys4 = keys;
			md5sig->alloced4++;
		}
		md5sig->entries4++;
		md5sig->keys4[md5sig->entries4 - 1].addr        = addr;
		md5sig->keys4[md5sig->entries4 - 1].base.key    = newkey;
		md5sig->keys4[md5sig->entries4 - 1].base.keylen = newkeylen;
	}
	return 0;
}
