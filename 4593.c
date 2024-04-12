P2PSocketHost* P2PSocketDispatcherHost::LookupSocket(
    int32 routing_id, int socket_id) {
  SocketsMap::iterator it = sockets_.find(
      ExtendedSocketId(routing_id, socket_id));
  if (it == sockets_.end())
    return NULL;
  else
    return it->second;
}
