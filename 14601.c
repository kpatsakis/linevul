bool socket_listen(const socket_t *socket, port_t port) {
  assert(socket != NULL);

 struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(LOCALHOST_);
  addr.sin_port = htons(port);
 if (bind(socket->fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    LOG_ERROR("%s unable to bind socket to port %u: %s", __func__, port, strerror(errno));
 return false;
 }

 if (listen(socket->fd, 10) == -1) {
    LOG_ERROR("%s unable to listen on port %u: %s", __func__, port, strerror(errno));
 return false;
 }

 return true;
}
