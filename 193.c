int SpdyProxyClientSocket::Write(IOBuffer* buf, int buf_len,
                                 const CompletionCallback& callback) {
  DCHECK(write_callback_.is_null());
  if (next_state_ != STATE_OPEN)
    return ERR_SOCKET_NOT_CONNECTED;

  DCHECK(spdy_stream_.get());
  spdy_stream_->SendData(buf, buf_len, MORE_DATA_TO_SEND);
  net_log_.AddByteTransferEvent(NetLog::TYPE_SOCKET_BYTES_SENT,
                                buf_len, buf->data());
  write_callback_ = callback;
  write_buffer_len_ = buf_len;
  return ERR_IO_PENDING;
}
