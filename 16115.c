  void BasicFindMainFallbackResponse(bool drop_from_working_set) {
    PushNextTask(base::BindOnce(
        &AppCacheStorageImplTest::Verify_BasicFindMainFallbackResponse,
        base::Unretained(this)));

    MakeCacheAndGroup(kManifestUrl, 2, 1, true);
    cache_->AddEntry(kEntryUrl, AppCacheEntry(AppCacheEntry::FALLBACK, 1));
    cache_->AddEntry(kEntryUrl2, AppCacheEntry(AppCacheEntry::FALLBACK, 2));
    cache_->fallback_namespaces_.push_back(AppCacheNamespace(
        APPCACHE_FALLBACK_NAMESPACE, kFallbackNamespace2, kEntryUrl2, false));
    cache_->fallback_namespaces_.push_back(AppCacheNamespace(
        APPCACHE_FALLBACK_NAMESPACE, kFallbackNamespace, kEntryUrl, false));
    AppCacheDatabase::CacheRecord cache_record;
    std::vector<AppCacheDatabase::EntryRecord> entries;
    std::vector<AppCacheDatabase::NamespaceRecord> intercepts;
    std::vector<AppCacheDatabase::NamespaceRecord> fallbacks;
    std::vector<AppCacheDatabase::OnlineWhiteListRecord> whitelists;
    cache_->ToDatabaseRecords(group_.get(), &cache_record, &entries,
                              &intercepts, &fallbacks, &whitelists);

    for (const auto& entry : entries) {
      if (entry.url != kDefaultEntryUrl)
        EXPECT_TRUE(database()->InsertEntry(&entry));
    }

    EXPECT_TRUE(database()->InsertNamespaceRecords(fallbacks));
    EXPECT_TRUE(database()->InsertOnlineWhiteListRecords(whitelists));
    if (drop_from_working_set) {
      EXPECT_TRUE(cache_->HasOneRef());
      cache_ = nullptr;
      EXPECT_TRUE(group_->HasOneRef());
      group_ = nullptr;
    }

    storage()->FindResponseForMainRequest(kFallbackTestUrl, GURL(), delegate());
    EXPECT_NE(kFallbackTestUrl, delegate()->found_url_);
  }
