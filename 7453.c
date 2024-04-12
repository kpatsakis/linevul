int UDPSocketLibevent::GetLocalAddress(IPEndPoint* address) const {
  DCHECK(CalledOnValidThread());
  DCHECK(address);
  if (!is_connected())
    return ERR_SOCKET_NOT_CONNECTED;

  if (!local_address_.get()) {
    SockaddrStorage storage;
    if (getsockname(socket_, storage.addr, &storage.addr_len))
      return MapSystemError(errno);
    scoped_ptr<IPEndPoint> address(new IPEndPoint());
    if (!address->FromSockAddr(storage.addr, storage.addr_len))
      return ERR_FAILED;
    local_address_.reset(address.release());
    net_log_.AddEvent(NetLog::TYPE_UDP_LOCAL_ADDRESS,
                      CreateNetLogUDPConnectCallback(local_address_.get()));
  }

  *address = *local_address_;
  return OK;
}
