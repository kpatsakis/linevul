void BackendIO::OpenEntry(const std::string& key, Entry** entry) {
  operation_ = OP_OPEN;
  key_ = key;
  entry_ptr_ = entry;
}
