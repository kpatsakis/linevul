int BlobURLRequestJob::BytesReadCompleted() {
  int bytes_read = read_buf_->BytesConsumed();
  read_buf_ = NULL;
  return bytes_read;
 }
