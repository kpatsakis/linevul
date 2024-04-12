void DocumentLoader::MarkAsCommitted() {
  DCHECK_LT(state_, kCommitted);
  state_ = kCommitted;
}
