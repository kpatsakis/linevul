kex_send_newkeys(struct ssh *ssh)
{
	int r;

	kex_reset_dispatch(ssh);
	if ((r = sshpkt_start(ssh, SSH2_MSG_NEWKEYS)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		return r;
	debug("SSH2_MSG_NEWKEYS sent");
	debug("expecting SSH2_MSG_NEWKEYS");
	ssh_dispatch_set(ssh, SSH2_MSG_NEWKEYS, &kex_input_newkeys);
	if (ssh->kex->ext_info_c)
		if ((r = kex_send_ext_info(ssh)) != 0)
			return r;
	return 0;
}
