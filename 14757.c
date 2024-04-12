void BackendIO::CreateEntry(const std::string& key, Entry** entry) {
  operation_ = OP_CREATE;
  key_ = key;
  entry_ptr_ = entry;
}
