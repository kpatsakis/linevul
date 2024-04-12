int ChunkedUploadDataStream::ReadInternal(IOBuffer* buf, int buf_len) {
  DCHECK_LT(0, buf_len);
  DCHECK(!read_buffer_.get());

  int result = ReadChunk(buf, buf_len);
  if (result == ERR_IO_PENDING) {
    read_buffer_ = buf;
    read_buffer_len_ = buf_len;
  }
  return result;
}
