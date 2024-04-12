SQLiteDatabase::SQLiteDatabase()
    : db_(nullptr),
      page_size_(-1),
      transaction_in_progress_(false),
      opening_thread_(0),
      open_error_(SQLITE_ERROR),
      open_error_message_(),
      last_changes_count_(0) {
}
