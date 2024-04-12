bool CancelableSyncSocket::CreatePair(CancelableSyncSocket* socket_a,
                                      CancelableSyncSocket* socket_b) {
  return CreatePairImpl(&socket_a->handle_, &socket_b->handle_, true);
}
