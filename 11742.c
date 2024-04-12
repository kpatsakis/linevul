HFSBTreeIterator::HFSBTreeIterator()
    : stream_(),
      header_(),
      leaf_records_read_(0),
      current_leaf_records_read_(0),
      current_leaf_number_(0),
      read_current_leaf_(false),
      leaf_data_(),
      current_leaf_offset_(0),
      current_leaf_() {
}
