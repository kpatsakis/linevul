void SQLiteDatabase::SetBusyTimeout(int ms) {
  if (db_)
    sqlite3_busy_timeout(db_, ms);
  else
    SQL_DVLOG(1) << "BusyTimeout set on non-open database";
}
