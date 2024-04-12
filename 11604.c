void DiskCacheBackendTest::BackendInvalidEntry9(bool eviction) {
  const int kSize = 0x3000;  // 12 kB.
  SetMaxSize(kSize * 10);
  InitCache();

  std::string first("some key");
  std::string second("something else");
  disk_cache::Entry* entry;
  ASSERT_THAT(CreateEntry(first, &entry), IsOk());
  entry->Close();
  ASSERT_THAT(CreateEntry(second, &entry), IsOk());

  disk_cache::EntryImpl* entry_impl =
      static_cast<disk_cache::EntryImpl*>(entry);

  entry_impl->entry()->Data()->state = 0xbad;
  entry_impl->entry()->Store();
  entry->Close();
  FlushQueueForTest();
  EXPECT_EQ(2, cache_->GetEntryCount());

  if (eviction) {
    TrimForTest(false);
    EXPECT_EQ(1, cache_->GetEntryCount());
    TrimForTest(false);
    EXPECT_EQ(1, cache_->GetEntryCount());
  } else {
    std::unique_ptr<TestIterator> iter = CreateIterator();
    EXPECT_NE(net::OK, iter->OpenNextEntry(&entry));

    ASSERT_THAT(iter->OpenNextEntry(&entry), IsOk());
    entry->Close();
    EXPECT_NE(net::OK, iter->OpenNextEntry(&entry));

    EXPECT_NE(net::OK, OpenEntry(second, &entry));
    EXPECT_EQ(2, cache_->GetEntryCount());
  }
  DisableIntegrityCheck();
}
