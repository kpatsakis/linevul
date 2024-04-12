int UDPSocketWin::InternalSendTo(IOBuffer* buf, int buf_len,
                                 const IPEndPoint* address) {
  DCHECK(!core_->write_iobuffer_);
  SockaddrStorage storage;
  struct sockaddr* addr = storage.addr;
  if (!address) {
    addr = NULL;
    storage.addr_len = 0;
  } else {
    if (!address->ToSockAddr(addr, &storage.addr_len)) {
      int result = ERR_FAILED;
      LogWrite(result, NULL, NULL);
      return result;
    }
  }

  WSABUF write_buffer;
  write_buffer.buf = buf->data();
  write_buffer.len = buf_len;

  DWORD flags = 0;
  DWORD num;
  AssertEventNotSignaled(core_->write_overlapped_.hEvent);
  int rv = WSASendTo(socket_, &write_buffer, 1, &num, flags,
                     addr, storage.addr_len, &core_->write_overlapped_, NULL);
  if (rv == 0) {
    if (ResetEventIfSignaled(core_->write_overlapped_.hEvent)) {
      int result = num;
      LogWrite(result, buf->data(), address);
      return result;
    }
  } else {
    int os_error = WSAGetLastError();
    if (os_error != WSA_IO_PENDING) {
      int result = MapSystemError(os_error);
      LogWrite(result, NULL, NULL);
      return result;
    }
  }

  core_->WatchForWrite();
  core_->write_iobuffer_ = buf;
  return ERR_IO_PENDING;
}
