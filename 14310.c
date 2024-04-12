void BackendIO::CancelSparseIO(EntryImpl* entry) {
  operation_ = OP_CANCEL_IO;
  entry_ = entry;
}
