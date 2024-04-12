bool DirectoryBackingStore::DeleteEntries(const MetahandleSet& handles) {
  if (handles.empty())
    return true;

  sqlite3* dbhandle = LazyGetSaveHandle();

  string query = "DELETE FROM metas WHERE metahandle IN (";
  for (MetahandleSet::const_iterator it = handles.begin(); it != handles.end();
       ++it) {
    if (it != handles.begin())
      query.append(",");
    query.append(base::Int64ToString(*it));
  }
  query.append(")");
  sqlite_utils::SQLStatement statement;
  int result = statement.prepare(dbhandle, query.data(), query.size());
  if (SQLITE_OK == result)
    result = statement.step();

  return SQLITE_DONE == result;
}
