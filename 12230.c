process_request_identities(SocketEntry *e, int version)
{
	Idtab *tab = idtab_lookup(version);
	Identity *id;
	struct sshbuf *msg;
	int r;

	if ((msg = sshbuf_new()) == NULL)
		fatal("%s: sshbuf_new failed", __func__);
	if ((r = sshbuf_put_u8(msg, (version == 1) ?
	    SSH_AGENT_RSA_IDENTITIES_ANSWER :
	    SSH2_AGENT_IDENTITIES_ANSWER)) != 0 ||
	    (r = sshbuf_put_u32(msg, tab->nentries)) != 0)
		fatal("%s: buffer error: %s", __func__, ssh_err(r));
	TAILQ_FOREACH(id, &tab->idlist, next) {
		if (id->key->type == KEY_RSA1) {
#ifdef WITH_SSH1
			if ((r = sshbuf_put_u32(msg,
			    BN_num_bits(id->key->rsa->n))) != 0 ||
			    (r = sshbuf_put_bignum1(msg,
			    id->key->rsa->e)) != 0 ||
			    (r = sshbuf_put_bignum1(msg,
			    id->key->rsa->n)) != 0)
				fatal("%s: buffer error: %s",
				    __func__, ssh_err(r));
#endif
		} else {
			u_char *blob;
			size_t blen;

			if ((r = sshkey_to_blob(id->key, &blob, &blen)) != 0) {
				error("%s: sshkey_to_blob: %s", __func__,
				    ssh_err(r));
				continue;
			}
			if ((r = sshbuf_put_string(msg, blob, blen)) != 0)
				fatal("%s: buffer error: %s",
				    __func__, ssh_err(r));
			free(blob);
		}
		if ((r = sshbuf_put_cstring(msg, id->comment)) != 0)
			fatal("%s: buffer error: %s", __func__, ssh_err(r));
	}
	if ((r = sshbuf_put_stringb(e->output, msg)) != 0)
		fatal("%s: buffer error: %s", __func__, ssh_err(r));
	sshbuf_free(msg);
}
