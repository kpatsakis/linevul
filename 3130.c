void GDataCache::ClearDirty(const std::string& resource_id,
                            const std::string& md5,
                            FileOperationType file_operation_type,
                            base::PlatformFileError* error) {
  AssertOnSequencedWorkerPool();
  DCHECK(error);

  scoped_ptr<CacheEntry> cache_entry =
      GetCacheEntry(resource_id, std::string());

  if (!cache_entry.get() ||
      cache_entry->sub_dir_type == CACHE_TYPE_PINNED) {
    LOG(WARNING) << "Can't clear dirty state of a file that wasn't cached: "
                 << "res_id=" << resource_id
                 << ", md5=" << md5;
    *error = base::PLATFORM_FILE_ERROR_NOT_FOUND;
    return;
  }

  if (!cache_entry->IsDirty()) {
    LOG(WARNING) << "Can't clear dirty state of a non-dirty file: res_id="
                 << resource_id
                 << ", md5=" << md5;
    *error = base::PLATFORM_FILE_ERROR_INVALID_OPERATION;
    return;
  }

  DCHECK_EQ(CACHE_TYPE_PERSISTENT, cache_entry->sub_dir_type);

  FilePath source_path = GetCacheFilePath(resource_id,
                                          md5,
                                          cache_entry->sub_dir_type,
                                          CACHED_FILE_LOCALLY_MODIFIED);

  CacheSubDirectoryType sub_dir_type =
      cache_entry->IsPinned() ? CACHE_TYPE_PERSISTENT : CACHE_TYPE_TMP;
  FilePath dest_path = GetCacheFilePath(resource_id,
                                        md5,
                                        sub_dir_type,
                                        CACHED_FILE_FROM_SERVER);

  FilePath symlink_path = GetCacheFilePath(resource_id,
                                           std::string(),
                                           CACHE_TYPE_OUTGOING,
                                           CACHED_FILE_FROM_SERVER);

  *error = ModifyCacheState(source_path,
                            dest_path,
                            file_operation_type,
                            symlink_path,
                            false /* don't create symlink */);

  if (*error == base::PLATFORM_FILE_OK && cache_entry->IsPinned()) {
    symlink_path = GetCacheFilePath(resource_id,
                                    std::string(),
                                    CACHE_TYPE_PINNED,
                                    CACHED_FILE_FROM_SERVER);

    *error = ModifyCacheState(dest_path,  // source path
                              dest_path,  // destination path
                              file_operation_type,
                              symlink_path,
                              true /* create symlink */);
  }

  if (*error == base::PLATFORM_FILE_OK) {
    int cache_state = ClearCacheDirty(cache_entry->cache_state);
    metadata_->UpdateCache(resource_id, md5, sub_dir_type, cache_state);
  }
}
