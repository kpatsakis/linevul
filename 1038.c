void SSLClientSocketOpenSSL::OnSendComplete(int result) {
  if (next_handshake_state_ == STATE_HANDSHAKE) {
    OnHandshakeIOComplete(result);
    return;
  }

  int rv_read = ERR_IO_PENDING;
  int rv_write = ERR_IO_PENDING;
  bool network_moved;
  do {
    if (user_read_buf_.get())
      rv_read = DoPayloadRead();
    if (user_write_buf_.get())
      rv_write = DoPayloadWrite();
    network_moved = DoTransportIO();
  } while (rv_read == ERR_IO_PENDING && rv_write == ERR_IO_PENDING &&
           (user_read_buf_.get() || user_write_buf_.get()) && network_moved);

  base::WeakPtr<SSLClientSocketOpenSSL> guard(weak_factory_.GetWeakPtr());
  if (user_read_buf_.get() && rv_read != ERR_IO_PENDING)
    DoReadCallback(rv_read);

  if (!guard.get())
    return;

  if (user_write_buf_.get() && rv_write != ERR_IO_PENDING)
    DoWriteCallback(rv_write);
}
