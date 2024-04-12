void DiskCacheBackendTest::BackendTransaction(const std::string& name,
                                              int num_entries,
                                              bool load) {
  success_ = false;
  ASSERT_TRUE(CopyTestCache(name));
  DisableFirstCleanup();

  uint32_t mask;
  if (load) {
    mask = 0xf;
    SetMaxSize(0x100000);
  } else {
    mask = 0;
    SetMaxSize(0);
  }
  SetMask(mask);

  InitCache();
  ASSERT_EQ(num_entries + 1, cache_->GetEntryCount());

  std::string key("the first key");
  disk_cache::Entry* entry1;
  ASSERT_NE(net::OK, OpenEntry(key, &entry1));

  int actual = cache_->GetEntryCount();
  if (num_entries != actual) {
    ASSERT_TRUE(load);
    ASSERT_EQ(num_entries - 1, actual);
  }

  cache_.reset();
  cache_impl_ = NULL;

  ASSERT_TRUE(CheckCacheIntegrity(cache_path_, new_eviction_, MaxSize(), mask));
  success_ = true;
}
