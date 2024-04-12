void DiskCacheBackendTest::BackendSetSize() {
  const int cache_size = 0x10000;  // 64 kB
  SetMaxSize(cache_size);
  InitCache();

  std::string first("some key");
  std::string second("something else");
  disk_cache::Entry* entry;
  ASSERT_THAT(CreateEntry(first, &entry), IsOk());

  scoped_refptr<net::IOBuffer> buffer(new net::IOBuffer(cache_size));
  memset(buffer->data(), 0, cache_size);
  EXPECT_EQ(cache_size / 10,
            WriteData(entry, 0, 0, buffer.get(), cache_size / 10, false))
      << "normal file";

  EXPECT_EQ(net::ERR_FAILED,
            WriteData(entry, 1, 0, buffer.get(), cache_size / 5, false))
      << "file size above the limit";

  SetMaxSize(cache_size * 2);
  EXPECT_EQ(cache_size / 5,
            WriteData(entry, 1, 0, buffer.get(), cache_size / 5, false));

  SetMaxSize(cache_size * 10);
  EXPECT_EQ(cache_size * 3 / 4,
            WriteData(entry, 0, 0, buffer.get(), cache_size * 3 / 4, false));
  entry->Close();
  FlushQueueForTest();

  SetMaxSize(cache_size);


  ASSERT_THAT(CreateEntry(second, &entry), IsOk());
  EXPECT_EQ(cache_size / 10,
            WriteData(entry, 0, 0, buffer.get(), cache_size / 10, false));

  disk_cache::Entry* entry2;
  ASSERT_THAT(CreateEntry("an extra key", &entry2), IsOk());
  EXPECT_EQ(cache_size / 10,
            WriteData(entry2, 0, 0, buffer.get(), cache_size / 10, false));
  entry2->Close();  // This will trigger the cache trim.

  EXPECT_NE(net::OK, OpenEntry(first, &entry2));

  FlushQueueForTest();  // Make sure that we are done trimming the cache.
  FlushQueueForTest();  // We may have posted two tasks to evict stuff.

  entry->Close();
  ASSERT_THAT(OpenEntry(second, &entry), IsOk());
  EXPECT_EQ(cache_size / 10, entry->GetDataSize(0));
  entry->Close();
}
