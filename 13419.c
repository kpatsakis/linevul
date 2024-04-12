kex_send_kexinit(struct ssh *ssh)
{
	u_char *cookie;
	struct kex *kex = ssh->kex;
	int r;

	if (kex == NULL)
		return SSH_ERR_INTERNAL_ERROR;
	if (kex->flags & KEX_INIT_SENT)
		return 0;
	kex->done = 0;

	/* generate a random cookie */
	if (sshbuf_len(kex->my) < KEX_COOKIE_LEN)
		return SSH_ERR_INVALID_FORMAT;
	if ((cookie = sshbuf_mutable_ptr(kex->my)) == NULL)
		return SSH_ERR_INTERNAL_ERROR;
	arc4random_buf(cookie, KEX_COOKIE_LEN);

	if ((r = sshpkt_start(ssh, SSH2_MSG_KEXINIT)) != 0 ||
	    (r = sshpkt_putb(ssh, kex->my)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		return r;
	debug("SSH2_MSG_KEXINIT sent");
	kex->flags |= KEX_INIT_SENT;
	return 0;
}
