int NaClIPCAdapter::RewrittenMessage::Read(char* dest_buffer,
                                           size_t dest_buffer_size) {
  CHECK(data_len_ >= data_read_cursor_);
  size_t bytes_to_write = std::min(dest_buffer_size,
                                   data_len_ - data_read_cursor_);
  if (bytes_to_write == 0)
    return 0;

  memcpy(dest_buffer, &data_[data_read_cursor_], bytes_to_write);
  data_read_cursor_ += bytes_to_write;
  return static_cast<int>(bytes_to_write);
}
