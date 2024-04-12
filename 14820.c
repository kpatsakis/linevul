void GDataFileSystem::UnpinIfPinned(
    const std::string& resource_id,
    const std::string& md5,
    bool success,
    const GDataCacheEntry& cache_entry) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  if (success && cache_entry.is_pinned())
    cache_->UnpinOnUIThread(resource_id, md5, CacheOperationCallback());
}
