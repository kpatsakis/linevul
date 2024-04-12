void GDataCache::Destroy() {
  AssertOnSequencedWorkerPool();
  delete this;
}
