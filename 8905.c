int64_t ResourceMultiBufferDataProvider::AvailableBytes() const {
  int64_t bytes = 0;
  for (const auto i : fifo_) {
    if (i->end_of_stream())
      break;
    bytes += i->data_size();
  }
  return bytes;
}
