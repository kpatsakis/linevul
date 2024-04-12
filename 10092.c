bool GDataCache::IsUnderGDataCacheDirectory(const FilePath& path) const {
  return cache_root_path_ == path || cache_root_path_.IsParent(path);
}
