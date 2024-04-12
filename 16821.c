after_select(fd_set *readset, fd_set *writeset)
{
	struct sockaddr_un sunaddr;
	socklen_t slen;
	char buf[1024];
	int len, sock, r;
	u_int i, orig_alloc;
	uid_t euid;
	gid_t egid;

	for (i = 0, orig_alloc = sockets_alloc; i < orig_alloc; i++)
		switch (sockets[i].type) {
		case AUTH_UNUSED:
			break;
		case AUTH_SOCKET:
			if (FD_ISSET(sockets[i].fd, readset)) {
				slen = sizeof(sunaddr);
				sock = accept(sockets[i].fd,
				    (struct sockaddr *)&sunaddr, &slen);
				if (sock < 0) {
					error("accept from AUTH_SOCKET: %s",
					    strerror(errno));
					break;
				}
				if (getpeereid(sock, &euid, &egid) < 0) {
					error("getpeereid %d failed: %s",
					    sock, strerror(errno));
					close(sock);
					break;
				}
				if ((euid != 0) && (getuid() != euid)) {
					error("uid mismatch: "
					    "peer euid %u != uid %u",
					    (u_int) euid, (u_int) getuid());
					close(sock);
					break;
				}
				new_socket(AUTH_CONNECTION, sock);
			}
			break;
		case AUTH_CONNECTION:
			if (sshbuf_len(sockets[i].output) > 0 &&
			    FD_ISSET(sockets[i].fd, writeset)) {
				len = write(sockets[i].fd,
				    sshbuf_ptr(sockets[i].output),
				    sshbuf_len(sockets[i].output));
				if (len == -1 && (errno == EAGAIN ||
				    errno == EINTR))
					continue;
				if (len <= 0) {
					close_socket(&sockets[i]);
					break;
				}
				if ((r = sshbuf_consume(sockets[i].output,
				    len)) != 0)
					fatal("%s: buffer error: %s",
					    __func__, ssh_err(r));
			}
			if (FD_ISSET(sockets[i].fd, readset)) {
				len = read(sockets[i].fd, buf, sizeof(buf));
				if (len == -1 && (errno == EAGAIN ||
				    errno == EINTR))
					continue;
				if (len <= 0) {
					close_socket(&sockets[i]);
					break;
				}
				if ((r = sshbuf_put(sockets[i].input,
				    buf, len)) != 0)
					fatal("%s: buffer error: %s",
					    __func__, ssh_err(r));
				explicit_bzero(buf, sizeof(buf));
				process_message(&sockets[i]);
			}
			break;
		default:
			fatal("Unknown type %d", sockets[i].type);
		}
}
