  bool DumpQuotaTableOnDBThread(QuotaDatabase* database) {
    DCHECK(database);
    return database->DumpQuotaTable(
        new TableCallback(base::Bind(&DumpQuotaTableHelper::AppendEntry,
                                     base::Unretained(this))));
  }
