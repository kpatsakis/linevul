bool AppCacheDatabase::FindOnlineWhiteListForCache(
    int64_t cache_id,
    std::vector<OnlineWhiteListRecord>* records) {
  DCHECK(records && records->empty());
  if (!LazyOpen(kDontCreate))
    return false;

  static const char kSql[] =
      "SELECT cache_id, namespace_url, is_pattern FROM OnlineWhiteLists"
      "  WHERE cache_id = ?";

  sql::Statement statement(db_->GetCachedStatement(SQL_FROM_HERE, kSql));
  statement.BindInt64(0, cache_id);

  while (statement.Step()) {
    records->push_back(OnlineWhiteListRecord());
    this->ReadOnlineWhiteListRecord(statement, &records->back());
    DCHECK(records->back().cache_id == cache_id);
  }
  return statement.Succeeded();
}
