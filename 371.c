void WebSocket::AddToReadBuffer(const char* data, int len) {
  DCHECK(current_read_buf_);
  if (len >= current_read_buf_->RemainingCapacity()) {
    current_read_buf_->SetCapacity(
        current_read_buf_->offset() + len);
  }

  DCHECK(current_read_buf_->RemainingCapacity() >= len);
  memcpy(current_read_buf_->data(), data, len);
  current_read_buf_->set_offset(current_read_buf_->offset() + len);
}
