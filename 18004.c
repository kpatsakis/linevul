mm_pty_allocate(int *ptyfd, int *ttyfd, char *namebuf, size_t namebuflen)
{
	Buffer m;
	char *p, *msg;
	int success = 0, tmp1 = -1, tmp2 = -1;

	/* Kludge: ensure there are fds free to receive the pty/tty */
	if ((tmp1 = dup(pmonitor->m_recvfd)) == -1 ||
	    (tmp2 = dup(pmonitor->m_recvfd)) == -1) {
		error("%s: cannot allocate fds for pty", __func__);
		if (tmp1 > 0)
			close(tmp1);
		if (tmp2 > 0)
			close(tmp2);
		return 0;
	}
	close(tmp1);
	close(tmp2);

	buffer_init(&m);
	mm_request_send(pmonitor->m_recvfd, MONITOR_REQ_PTY, &m);

	debug3("%s: waiting for MONITOR_ANS_PTY", __func__);
	mm_request_receive_expect(pmonitor->m_recvfd, MONITOR_ANS_PTY, &m);

	success = buffer_get_int(&m);
	if (success == 0) {
		debug3("%s: pty alloc failed", __func__);
		buffer_free(&m);
		return (0);
	}
	p = buffer_get_string(&m, NULL);
	msg = buffer_get_string(&m, NULL);
	buffer_free(&m);

	strlcpy(namebuf, p, namebuflen); /* Possible truncation */
	free(p);

	buffer_append(&loginmsg, msg, strlen(msg));
	free(msg);

	if ((*ptyfd = mm_receive_fd(pmonitor->m_recvfd)) == -1 ||
	    (*ttyfd = mm_receive_fd(pmonitor->m_recvfd)) == -1)
		fatal("%s: receive fds failed", __func__);

	/* Success */
	return (1);
}
