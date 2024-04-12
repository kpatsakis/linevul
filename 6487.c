bool AppCacheDatabase::LazyOpen(bool create_if_needed) {
  if (db_)
    return true;

  if (is_disabled_)
    return false;

  bool use_in_memory_db = db_file_path_.empty();
  if (!create_if_needed &&
      (use_in_memory_db || !base::PathExists(db_file_path_))) {
    return false;
  }

  db_.reset(new sql::Database);
  meta_table_.reset(new sql::MetaTable);

  db_->set_histogram_tag("AppCache");

  bool opened = false;
  if (use_in_memory_db) {
    opened = db_->OpenInMemory();
  } else if (!base::CreateDirectory(db_file_path_.DirName())) {
    LOG(ERROR) << "Failed to create appcache directory.";
  } else {
    opened = db_->Open(db_file_path_);
    if (opened)
      db_->Preload();
  }

  if (!opened || !db_->QuickIntegrityCheck() || !EnsureDatabaseVersion()) {
    LOG(ERROR) << "Failed to open the appcache database.";
    AppCacheHistograms::CountInitResult(
        AppCacheHistograms::SQL_DATABASE_ERROR);

    if (!use_in_memory_db && DeleteExistingAndCreateNewDatabase())
      return true;

    Disable();
    return false;
  }

  AppCacheHistograms::CountInitResult(AppCacheHistograms::INIT_OK);
  was_corruption_detected_ = false;
  db_->set_error_callback(base::BindRepeating(
      &AppCacheDatabase::OnDatabaseError, base::Unretained(this)));
  return true;
}
