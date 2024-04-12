void AppCacheDatabase::ReadNamespaceRecord(
    const sql::Statement* statement, NamespaceRecord* record) {
  record->cache_id = statement->ColumnInt64(0);
  record->origin = url::Origin::Create(GURL(statement->ColumnString(1)));
  record->namespace_.type =
      static_cast<AppCacheNamespaceType>(statement->ColumnInt(2));
  record->namespace_.namespace_url = GURL(statement->ColumnString(3));
  record->namespace_.target_url = GURL(statement->ColumnString(4));
  record->namespace_.is_pattern = statement->ColumnBool(5);
  DCHECK(record->namespace_.type == APPCACHE_FALLBACK_NAMESPACE ||
         record->namespace_.type == APPCACHE_INTERCEPT_NAMESPACE);
}
