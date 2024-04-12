void WebSocket::SendPending() {
  DCHECK(MessageLoop::current() == origin_loop_);
  DCHECK(socket_stream_);
  if (!current_write_buf_) {
    if (pending_write_bufs_.empty())
      return;
    current_write_buf_ = new DrainableIOBuffer(
        pending_write_bufs_.front(), pending_write_bufs_.front()->size());
  }
  DCHECK_GT(current_write_buf_->BytesRemaining(), 0);
  bool sent = socket_stream_->SendData(
      current_write_buf_->data(),
      std::min(current_write_buf_->BytesRemaining(),
               max_pending_send_allowed_));
  DCHECK(sent);
}
