bool AppCacheDatabase::DeleteCache(int64_t cache_id) {
  if (!LazyOpen(kDontCreate))
    return false;

  static const char kSql[] = "DELETE FROM Caches WHERE cache_id = ?";

  sql::Statement statement(db_->GetCachedStatement(SQL_FROM_HERE, kSql));
  statement.BindInt64(0, cache_id);

  return statement.Run();
}
