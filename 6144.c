void BackendIO::EndEnumeration(std::unique_ptr<Rankings::Iterator> iterator) {
  operation_ = OP_END_ENUMERATION;
  scoped_iterator_ = std::move(iterator);
}
