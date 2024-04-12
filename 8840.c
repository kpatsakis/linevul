muxserver_listen(void)
{
	mode_t old_umask;
	char *orig_control_path = options.control_path;
	char rbuf[16+1];
	u_int i, r;
	int oerrno;

	if (options.control_path == NULL ||
	    options.control_master == SSHCTL_MASTER_NO)
		return;

	debug("setting up multiplex master socket");

	/*
	 * Use a temporary path before listen so we can pseudo-atomically
	 * establish the listening socket in its final location to avoid
	 * other processes racing in between bind() and listen() and hitting
	 * an unready socket.
	 */
	for (i = 0; i < sizeof(rbuf) - 1; i++) {
		r = arc4random_uniform(26+26+10);
		rbuf[i] = (r < 26) ? 'a' + r :
		    (r < 26*2) ? 'A' + r - 26 :
		    '0' + r - 26 - 26;
	}
	rbuf[sizeof(rbuf) - 1] = '\0';
	options.control_path = NULL;
	xasprintf(&options.control_path, "%s.%s", orig_control_path, rbuf);
	debug3("%s: temporary control path %s", __func__, options.control_path);

	old_umask = umask(0177);
	muxserver_sock = unix_listener(options.control_path, 64, 0);
	oerrno = errno;
	umask(old_umask);
	if (muxserver_sock < 0) {
		if (oerrno == EINVAL || oerrno == EADDRINUSE) {
			error("ControlSocket %s already exists, "
			    "disabling multiplexing", options.control_path);
 disable_mux_master:
			if (muxserver_sock != -1) {
				close(muxserver_sock);
				muxserver_sock = -1;
			}
			free(orig_control_path);
			free(options.control_path);
			options.control_path = NULL;
			options.control_master = SSHCTL_MASTER_NO;
			return;
		} else {
			/* unix_listener() logs the error */
			cleanup_exit(255);
		}
	}

	/* Now atomically "move" the mux socket into position */
	if (link(options.control_path, orig_control_path) != 0) {
		if (errno != EEXIST) {
			fatal("%s: link mux listener %s => %s: %s", __func__, 
			    options.control_path, orig_control_path,
			    strerror(errno));
		}
		error("ControlSocket %s already exists, disabling multiplexing",
		    orig_control_path);
		unlink(options.control_path);
		goto disable_mux_master;
	}
	unlink(options.control_path);
	free(options.control_path);
	options.control_path = orig_control_path;

	set_nonblock(muxserver_sock);

	mux_listener_channel = channel_new("mux listener",
	    SSH_CHANNEL_MUX_LISTENER, muxserver_sock, muxserver_sock, -1,
	    CHAN_TCP_WINDOW_DEFAULT, CHAN_TCP_PACKET_DEFAULT,
	    0, options.control_path, 1);
	mux_listener_channel->mux_rcb = mux_master_read_cb;
	debug3("%s: mux listener channel %d fd %d", __func__,
	    mux_listener_channel->self, mux_listener_channel->sock);
}
