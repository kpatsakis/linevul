BytesConsumer::Result ReadableStreamBytesConsumer::EndRead(size_t read_size) {
  DCHECK(pending_buffer_);
  DCHECK_LE(pending_offset_ + read_size, pending_buffer_->length());
  pending_offset_ += read_size;
  if (pending_offset_ >= pending_buffer_->length()) {
    pending_buffer_ = nullptr;
    pending_offset_ = 0;
  }
  return Result::kOk;
}
