process_sign_request2(SocketEntry *e)
{
	u_char *blob, *data, *signature = NULL;
	size_t blen, dlen, slen = 0;
	u_int compat = 0, flags;
	int r, ok = -1;
	struct sshbuf *msg;
	struct sshkey *key;
	struct identity *id;

	if ((msg = sshbuf_new()) == NULL)
		fatal("%s: sshbuf_new failed", __func__);
	if ((r = sshbuf_get_string(e->request, &blob, &blen)) != 0 ||
	    (r = sshbuf_get_string(e->request, &data, &dlen)) != 0 ||
	    (r = sshbuf_get_u32(e->request, &flags)) != 0)
		fatal("%s: buffer error: %s", __func__, ssh_err(r));
	if (flags & SSH_AGENT_OLD_SIGNATURE)
		compat = SSH_BUG_SIGBLOB;
	if ((r = sshkey_from_blob(blob, blen, &key)) != 0) {
		error("%s: cannot parse key blob: %s", __func__, ssh_err(r));
		goto send;
	}
	if ((id = lookup_identity(key, 2)) == NULL) {
		verbose("%s: %s key not found", __func__, sshkey_type(key));
		goto send;
	}
	if (id->confirm && confirm_key(id) != 0) {
		verbose("%s: user refused key", __func__);
		goto send;
	}
	if ((r = sshkey_sign(id->key, &signature, &slen,
	    data, dlen, agent_decode_alg(key, flags), compat)) != 0) {
		error("%s: sshkey_sign: %s", __func__, ssh_err(r));
		goto send;
	}
	/* Success */
	ok = 0;
 send:
	sshkey_free(key);
	if (ok == 0) {
		if ((r = sshbuf_put_u8(msg, SSH2_AGENT_SIGN_RESPONSE)) != 0 ||
		    (r = sshbuf_put_string(msg, signature, slen)) != 0)
			fatal("%s: buffer error: %s", __func__, ssh_err(r));
	} else if ((r = sshbuf_put_u8(msg, SSH_AGENT_FAILURE)) != 0)
		fatal("%s: buffer error: %s", __func__, ssh_err(r));

	if ((r = sshbuf_put_stringb(e->output, msg)) != 0)
		fatal("%s: buffer error: %s", __func__, ssh_err(r));

	sshbuf_free(msg);
	free(data);
	free(blob);
	free(signature);
}
