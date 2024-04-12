int64_t ResourceMultiBufferDataProvider::byte_pos() const {
  int64_t ret = pos_;
  ret += fifo_.size();
  ret = ret << url_data_->multibuffer()->block_size_shift();
  if (!fifo_.empty()) {
    ret += fifo_.back()->data_size() - block_size();
  }
  return ret;
}
