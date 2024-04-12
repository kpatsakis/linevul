  void Verify_LoadCache_Far_Hit() {
    EXPECT_TRUE(delegate()->loaded_cache_.get());
    EXPECT_TRUE(delegate()->loaded_cache_->HasOneRef());
    EXPECT_EQ(1, delegate()->loaded_cache_id_);

    EXPECT_TRUE(delegate()->loaded_cache_->owning_group());
    EXPECT_TRUE(delegate()->loaded_cache_->owning_group()->HasOneRef());
    EXPECT_EQ(1, delegate()->loaded_cache_->owning_group()->group_id());

    EXPECT_EQ(1, mock_quota_manager_proxy_->notify_storage_accessed_count_);
    EXPECT_EQ(0, mock_quota_manager_proxy_->notify_storage_modified_count_);

    delegate()->loaded_cache_ = nullptr;
    EXPECT_FALSE(delegate()->loaded_group_.get());

    PushNextTask(
        base::BindOnce(&AppCacheStorageImplTest::Verify_LoadGroup_Far_Hit,
                       base::Unretained(this)));

    storage()->LoadOrCreateGroup(kManifestUrl, delegate());
  }
