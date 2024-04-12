void BackendImpl::TrimForTest(bool empty) {
  eviction_.SetTestMode();
  eviction_.TrimCache(empty);
}
