  void VerifyCacheFileState(base::PlatformFileError error,
                            const std::string& resource_id,
                            const std::string& md5) {
    ++num_callback_invocations_;

    EXPECT_EQ(expected_error_, error);

    GDataRootDirectory::CacheEntry* entry =
        file_system_->root_->GetCacheEntry(resource_id, md5);
    if (GDataFile::IsCachePresent(expected_cache_state_) ||
        GDataFile::IsCachePinned(expected_cache_state_)) {
      ASSERT_TRUE(entry != NULL);
      EXPECT_EQ(expected_cache_state_, entry->cache_state);
      EXPECT_EQ(expected_sub_dir_type_, entry->sub_dir_type);
    } else {
      EXPECT_TRUE(entry == NULL);
    }

    FilePath dest_path = file_system_->GetCacheFilePath(
        resource_id,
        md5,
        GDataFile::IsCachePinned(expected_cache_state_) ||
            GDataFile::IsCacheDirty(expected_cache_state_) ?
                GDataRootDirectory::CACHE_TYPE_PERSISTENT :
                GDataRootDirectory::CACHE_TYPE_TMP,
        GDataFile::IsCacheDirty(expected_cache_state_) ?
            GDataFileSystem::CACHED_FILE_LOCALLY_MODIFIED :
            GDataFileSystem::CACHED_FILE_FROM_SERVER);
    bool exists = file_util::PathExists(dest_path);
    if (GDataFile::IsCachePresent(expected_cache_state_))
      EXPECT_TRUE(exists);
    else
      EXPECT_FALSE(exists);

    FilePath symlink_path = file_system_->GetCacheFilePath(
        resource_id,
        std::string(),
        GDataRootDirectory::CACHE_TYPE_PINNED,
        GDataFileSystem::CACHED_FILE_FROM_SERVER);
    exists = file_util::IsLink(symlink_path);
    if (GDataFile::IsCachePinned(expected_cache_state_)) {
      EXPECT_TRUE(exists);
      FilePath target_path;
      EXPECT_TRUE(file_util::ReadSymbolicLink(symlink_path, &target_path));
      if (GDataFile::IsCachePresent(expected_cache_state_))
        EXPECT_EQ(dest_path, target_path);
      else
        EXPECT_EQ(kSymLinkToDevNull, target_path.value());
    } else {
      EXPECT_FALSE(exists);
    }

    symlink_path = file_system_->GetCacheFilePath(
        resource_id,
        std::string(),
        GDataRootDirectory::CACHE_TYPE_OUTGOING,
        GDataFileSystem::CACHED_FILE_FROM_SERVER);
    exists = file_util::IsLink(symlink_path);
    if (expect_outgoing_symlink_ &&
        GDataFile::IsCacheDirty(expected_cache_state_)) {
      EXPECT_TRUE(exists);
      FilePath target_path;
      EXPECT_TRUE(file_util::ReadSymbolicLink(symlink_path, &target_path));
      EXPECT_TRUE(target_path.value() != kSymLinkToDevNull);
      if (GDataFile::IsCachePresent(expected_cache_state_))
        EXPECT_EQ(dest_path, target_path);
    } else {
      EXPECT_FALSE(exists);
    }
  }
