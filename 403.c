int corruptPageError(int lineno, MemPage *p){
  char *zMsg;
  sqlite3BeginBenignMalloc();
  zMsg = sqlite3_mprintf("database corruption page %d of %s",
      (int)p->pgno, sqlite3PagerFilename(p->pBt->pPager, 0)
  );
  sqlite3EndBenignMalloc();
  if( zMsg ){
    sqlite3ReportError(SQLITE_CORRUPT, lineno, zMsg);
  }
  sqlite3_free(zMsg);
  return SQLITE_CORRUPT_BKPT;
}
