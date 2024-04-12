 void DiskCacheBackendTest::BackendDoomBetween() {
   InitCache();
 
  disk_cache::Entry* entry;
  ASSERT_THAT(CreateEntry("first", &entry), IsOk());
  entry->Close();
  FlushQueueForTest();

  AddDelay();
  Time middle_start = Time::Now();

  ASSERT_THAT(CreateEntry("second", &entry), IsOk());
  entry->Close();
  ASSERT_THAT(CreateEntry("third", &entry), IsOk());
  entry->Close();
  FlushQueueForTest();

  AddDelay();
  Time middle_end = Time::Now();

  ASSERT_THAT(CreateEntry("fourth", &entry), IsOk());
  entry->Close();
  ASSERT_THAT(OpenEntry("fourth", &entry), IsOk());
  entry->Close();
  FlushQueueForTest();

  AddDelay();
  Time final = Time::Now();

  ASSERT_EQ(4, cache_->GetEntryCount());
  EXPECT_THAT(DoomEntriesBetween(middle_start, middle_end), IsOk());
  ASSERT_EQ(2, cache_->GetEntryCount());

  ASSERT_THAT(OpenEntry("fourth", &entry), IsOk());
  entry->Close();

  EXPECT_THAT(DoomEntriesBetween(middle_start, final), IsOk());
  ASSERT_EQ(1, cache_->GetEntryCount());

  ASSERT_THAT(OpenEntry("first", &entry), IsOk());
  entry->Close();
}
