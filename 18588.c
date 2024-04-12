void DiskCacheBackendTest::BackendDoomMidEnumeration() {
  InitCache();

  const int kNumEntries = 100;
  std::set<std::string> keys;
  for (int i = 0; i < kNumEntries; i++) {
    std::string key = GenerateKey(true);
    keys.insert(key);
    disk_cache::Entry* entry;
    ASSERT_THAT(CreateEntry(key, &entry), IsOk());
    entry->Close();
  }

  disk_cache::Entry* entry;
  std::unique_ptr<TestIterator> iter = CreateIterator();
  int count = 0;
  while (iter->OpenNextEntry(&entry) == net::OK) {
    if (count == 0) {
      auto key_to_doom = keys.begin();
      while (*key_to_doom == entry->GetKey())
        key_to_doom++;
      ASSERT_THAT(DoomEntry(*key_to_doom), IsOk());
      ASSERT_EQ(1u, keys.erase(*key_to_doom));
    }
    ASSERT_NE(nullptr, entry);
    EXPECT_EQ(1u, keys.erase(entry->GetKey()));
    entry->Close();
    count++;
  };

  EXPECT_EQ(kNumEntries - 1, cache_->GetEntryCount());
  EXPECT_EQ(0u, keys.size());
}
