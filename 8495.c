int ctdb_tcp_listen(struct ctdb_context *ctdb)
{
	struct ctdb_tcp *ctcp = talloc_get_type(ctdb->private_data,
						struct ctdb_tcp);
        ctdb_sock_addr sock;
	int sock_size;
	int one = 1;
	struct tevent_fd *fde;

	/* we can either auto-bind to the first available address, or we can
	   use a specified address */
	if (!ctdb->address.address) {
		return ctdb_tcp_listen_automatic(ctdb);
	}

	ZERO_STRUCT(sock);
	if (ctdb_tcp_get_address(ctdb, ctdb->address.address, 
				 &sock) != 0) {
		goto failed;
	}
	
	switch (sock.sa.sa_family) {
	case AF_INET:
		sock.ip.sin_port = htons(ctdb->address.port);
		sock_size = sizeof(sock.ip);
		break;
	case AF_INET6:
		sock.ip6.sin6_port = htons(ctdb->address.port);
		sock_size = sizeof(sock.ip6);
		break;
	default:
		DEBUG(DEBUG_ERR, (__location__ " unknown family %u\n",
			sock.sa.sa_family));
		goto failed;
	}
#ifdef HAVE_SOCK_SIN_LEN
	sock.ip.sin_len = sock_size;
#endif

	ctcp->listen_fd = socket(sock.sa.sa_family, SOCK_STREAM, IPPROTO_TCP);
	if (ctcp->listen_fd == -1) {
		ctdb_set_error(ctdb, "socket failed\n");
		return -1;
	}

	set_close_on_exec(ctcp->listen_fd);

        setsockopt(ctcp->listen_fd,SOL_SOCKET,SO_REUSEADDR,(char *)&one,sizeof(one));

	if (bind(ctcp->listen_fd, (struct sockaddr * )&sock, sock_size) != 0) {
		DEBUG(DEBUG_ERR,(__location__ " Failed to bind() to socket. %s(%d)\n", strerror(errno), errno));
		goto failed;
	}

	if (listen(ctcp->listen_fd, 10) == -1) {
		goto failed;
	}

	fde = event_add_fd(ctdb->ev, ctcp, ctcp->listen_fd, EVENT_FD_READ,
		     ctdb_listen_event, ctdb);	
	tevent_fd_set_auto_close(fde);

	return 0;

failed:
	if (ctcp->listen_fd != -1) {
		close(ctcp->listen_fd);
	}
	ctcp->listen_fd = -1;
	return -1;
}
