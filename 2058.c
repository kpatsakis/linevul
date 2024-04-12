bool AppCacheDatabase::FindLastStorageIds(
    int64_t* last_group_id,
    int64_t* last_cache_id,
    int64_t* last_response_id,
    int64_t* last_deletable_response_rowid) {
  DCHECK(last_group_id && last_cache_id && last_response_id &&
         last_deletable_response_rowid);

  *last_group_id = 0;
  *last_cache_id = 0;
  *last_response_id = 0;
  *last_deletable_response_rowid = 0;

  if (!LazyOpen(kDontCreate))
    return false;

  static const char kMaxGroupIdSql[] = "SELECT MAX(group_id) FROM Groups";
  static const char kMaxCacheIdSql[] = "SELECT MAX(cache_id) FROM Caches";
  static const char kMaxResponseIdFromEntriesSql[] =
      "SELECT MAX(response_id) FROM Entries";
  static const char kMaxResponseIdFromDeletablesSql[] =
      "SELECT MAX(response_id) FROM DeletableResponseIds";
  static const char kMaxDeletableResponseRowIdSql[] =
      "SELECT MAX(rowid) FROM DeletableResponseIds";
  int64_t max_group_id;
  int64_t max_cache_id;
  int64_t max_response_id_from_entries;
  int64_t max_response_id_from_deletables;
  int64_t max_deletable_response_rowid;
  if (!RunUniqueStatementWithInt64Result(kMaxGroupIdSql, &max_group_id) ||
      !RunUniqueStatementWithInt64Result(kMaxCacheIdSql, &max_cache_id) ||
      !RunUniqueStatementWithInt64Result(kMaxResponseIdFromEntriesSql,
                                         &max_response_id_from_entries) ||
      !RunUniqueStatementWithInt64Result(kMaxResponseIdFromDeletablesSql,
                                         &max_response_id_from_deletables) ||
      !RunUniqueStatementWithInt64Result(kMaxDeletableResponseRowIdSql,
                                         &max_deletable_response_rowid)) {
    return false;
  }

  *last_group_id = max_group_id;
  *last_cache_id = max_cache_id;
  *last_response_id = std::max(max_response_id_from_entries,
                               max_response_id_from_deletables);
  *last_deletable_response_rowid = max_deletable_response_rowid;
  return true;
}
