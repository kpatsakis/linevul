bool AppCacheDatabase::LazyUpdateLastAccessTime(int64_t group_id,
                                                base::Time time) {
  if (!LazyOpen(kCreateIfNeeded))
    return false;
  lazy_last_access_times_[group_id] = time;
  return true;
}
