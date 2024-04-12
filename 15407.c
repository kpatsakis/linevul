int UDPSocketWin::SendToOrWrite(IOBuffer* buf,
                                int buf_len,
                                const IPEndPoint* address,
                                const CompletionCallback& callback) {
  DCHECK(CalledOnValidThread());
  DCHECK_NE(INVALID_SOCKET, socket_);
  DCHECK(write_callback_.is_null());
  DCHECK(!callback.is_null());  // Synchronous operation not supported.
  DCHECK_GT(buf_len, 0);
  DCHECK(!send_to_address_.get());

  int nwrite = InternalSendTo(buf, buf_len, address);
  if (nwrite != ERR_IO_PENDING)
    return nwrite;

  if (address)
    send_to_address_.reset(new IPEndPoint(*address));
  write_callback_ = callback;
  return ERR_IO_PENDING;
}
