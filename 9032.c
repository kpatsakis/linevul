notify_setup(void)
{
	if (pipe(notify_pipe) < 0) {
		error("pipe(notify_pipe) failed %s", strerror(errno));
	} else if ((fcntl(notify_pipe[0], F_SETFD, FD_CLOEXEC) == -1) ||
	    (fcntl(notify_pipe[1], F_SETFD, FD_CLOEXEC) == -1)) {
		error("fcntl(notify_pipe, F_SETFD) failed %s", strerror(errno));
		close(notify_pipe[0]);
		close(notify_pipe[1]);
	} else {
		set_nonblock(notify_pipe[0]);
		set_nonblock(notify_pipe[1]);
		return;
	}
	notify_pipe[0] = -1;	/* read end */
	notify_pipe[1] = -1;	/* write end */
}
