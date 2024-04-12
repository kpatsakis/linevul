void user_revoke(struct key *key)
{
	struct user_key_payload *upayload = user_key_payload_locked(key);

	/* clear the quota */
	key_payload_reserve(key, 0);

	if (upayload) {
		rcu_assign_keypointer(key, NULL);
		call_rcu(&upayload->rcu, user_free_payload_rcu);
	}
}
