static int php_sockop_close(php_stream *stream, int close_handle)
{
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;
#ifdef PHP_WIN32
	int n;
#endif

	if (!sock) {
		return 0;
	}

	if (close_handle) {

#ifdef PHP_WIN32
		if (sock->socket == -1)
			sock->socket = SOCK_ERR;
#endif
		if (sock->socket != SOCK_ERR) {
#ifdef PHP_WIN32
			/* prevent more data from coming in */
			shutdown(sock->socket, SHUT_RD);

			/* try to make sure that the OS sends all data before we close the connection.
			 * Essentially, we are waiting for the socket to become writeable, which means
			 * that all pending data has been sent.
			 * We use a small timeout which should encourage the OS to send the data,
			 * but at the same time avoid hanging indefinitely.
			 * */
			do {
				n = php_pollfd_for_ms(sock->socket, POLLOUT, 500);
			} while (n == -1 && php_socket_errno() == EINTR);
#endif
			closesocket(sock->socket);
			sock->socket = SOCK_ERR;
		}

	}

	pefree(sock, php_stream_is_persistent(stream));

	return 0;
}
