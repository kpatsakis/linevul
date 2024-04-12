bool AppCacheDatabase::CreateSchema() {
  sql::Transaction transaction(db_.get());
  if (!transaction.Begin())
    return false;

  if (!meta_table_->Init(db_.get(), kCurrentVersion, kCompatibleVersion))
    return false;

  if (!meta_table_->SetValue(kExperimentFlagsKey,
                             GetActiveExperimentFlags())) {
    return false;
  }

  for (int i = 0; i < kTableCount; ++i) {
    if (!CreateTable(db_.get(), kTables[i]))
      return false;
  }

  for (int i = 0; i < kIndexCount; ++i) {
    if (!CreateIndex(db_.get(), kIndexes[i]))
      return false;
  }

  return transaction.Commit();
 }
