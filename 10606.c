bool UDPSocketWin::SetReceiveBufferSize(int32 size) {
  DCHECK(CalledOnValidThread());
  int rv = setsockopt(socket_, SOL_SOCKET, SO_RCVBUF,
                      reinterpret_cast<const char*>(&size), sizeof(size));
  DCHECK(!rv) << "Could not set socket receive buffer size: " << errno;
  return rv == 0;
}
