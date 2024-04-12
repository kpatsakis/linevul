server_accept_inetd(int *sock_in, int *sock_out)
{
	int fd;

	startup_pipe = -1;
	if (rexeced_flag) {
		close(REEXEC_CONFIG_PASS_FD);
		*sock_in = *sock_out = dup(STDIN_FILENO);
		if (!debug_flag) {
			startup_pipe = dup(REEXEC_STARTUP_PIPE_FD);
			close(REEXEC_STARTUP_PIPE_FD);
		}
	} else {
		*sock_in = dup(STDIN_FILENO);
		*sock_out = dup(STDOUT_FILENO);
	}
	/*
	 * We intentionally do not close the descriptors 0, 1, and 2
	 * as our code for setting the descriptors won't work if
	 * ttyfd happens to be one of those.
	 */
	if ((fd = open(_PATH_DEVNULL, O_RDWR, 0)) != -1) {
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		if (!log_stderr)
			dup2(fd, STDERR_FILENO);
		if (fd > (log_stderr ? STDERR_FILENO : STDOUT_FILENO))
			close(fd);
	}
	debug("inetd sockets after dupping: %d, %d", *sock_in, *sock_out);
}
