struct key *request_key_auth_new(struct key *target, const void *callout_info,
				 size_t callout_len, struct key *dest_keyring)
{
	struct request_key_auth *rka, *irka;
	const struct cred *cred = current->cred;
	struct key *authkey = NULL;
	char desc[20];
	int ret = -ENOMEM;

	kenter("%d,", target->serial);

	/* allocate a auth record */
	rka = kzalloc(sizeof(*rka), GFP_KERNEL);
	if (!rka)
		goto error;
	rka->callout_info = kmemdup(callout_info, callout_len, GFP_KERNEL);
	if (!rka->callout_info)
		goto error_free_rka;
	rka->callout_len = callout_len;

	/* see if the calling process is already servicing the key request of
	 * another process */
	if (cred->request_key_auth) {
		/* it is - use that instantiation context here too */
		down_read(&cred->request_key_auth->sem);

		/* if the auth key has been revoked, then the key we're
		 * servicing is already instantiated */
		if (test_bit(KEY_FLAG_REVOKED,
			     &cred->request_key_auth->flags)) {
			up_read(&cred->request_key_auth->sem);
			ret = -EKEYREVOKED;
			goto error_free_rka;
		}

		irka = cred->request_key_auth->payload.data[0];
		rka->cred = get_cred(irka->cred);
		rka->pid = irka->pid;

		up_read(&cred->request_key_auth->sem);
	}
	else {
		/* it isn't - use this process as the context */
		rka->cred = get_cred(cred);
		rka->pid = current->pid;
	}

	rka->target_key = key_get(target);
	rka->dest_keyring = key_get(dest_keyring);

	/* allocate the auth key */
	sprintf(desc, "%x", target->serial);

	authkey = key_alloc(&key_type_request_key_auth, desc,
			    cred->fsuid, cred->fsgid, cred,
			    KEY_POS_VIEW | KEY_POS_READ | KEY_POS_SEARCH |
			    KEY_USR_VIEW, KEY_ALLOC_NOT_IN_QUOTA, NULL);
	if (IS_ERR(authkey)) {
		ret = PTR_ERR(authkey);
		goto error_free_rka;
	}

	/* construct the auth key */
	ret = key_instantiate_and_link(authkey, rka, 0, NULL, NULL);
	if (ret < 0)
		goto error_put_authkey;

	kleave(" = {%d,%d}", authkey->serial, refcount_read(&authkey->usage));
	return authkey;

error_put_authkey:
	key_put(authkey);
error_free_rka:
	free_request_key_auth(rka);
error:
	kleave("= %d", ret);
	return ERR_PTR(ret);
}