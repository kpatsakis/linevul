void GDataCache::CommitDirty(const std::string& resource_id,
                             const std::string& md5,
                             FileOperationType file_operation_type,
                             base::PlatformFileError* error) {
  AssertOnSequencedWorkerPool();
  DCHECK(error);

  scoped_ptr<CacheEntry> cache_entry =
      GetCacheEntry(resource_id, std::string());

  if (!cache_entry.get() ||
      cache_entry->sub_dir_type == CACHE_TYPE_PINNED) {
    LOG(WARNING) << "Can't commit dirty a file that wasn't cached: res_id="
                 << resource_id
                 << ", md5=" << md5;
    *error = base::PLATFORM_FILE_ERROR_NOT_FOUND;
    return;
  }

  if (!cache_entry->IsDirty()) {
    LOG(WARNING) << "Can't commit a non-dirty file: res_id="
                 << resource_id
                 << ", md5=" << md5;
    *error = base::PLATFORM_FILE_ERROR_INVALID_OPERATION;
    return;
  }

  DCHECK_EQ(CACHE_TYPE_PERSISTENT, cache_entry->sub_dir_type);

  FilePath symlink_path = GetCacheFilePath(resource_id,
                                           std::string(),
                                           CACHE_TYPE_OUTGOING,
                                           CACHED_FILE_FROM_SERVER);

  FilePath target_path = GetCacheFilePath(resource_id,
                                          md5,
                                          cache_entry->sub_dir_type,
                                          CACHED_FILE_LOCALLY_MODIFIED);

  *error = ModifyCacheState(target_path,  // source
                            target_path,  // destination
                            file_operation_type,
                            symlink_path,
                            true /* create symlink */);
}
