static int bindText(
  sqlite3_stmt *pStmt,   /* The statement to bind against */
  int i,                 /* Index of the parameter to bind */
  const void *zData,     /* Pointer to the data to be bound */
  int nData,             /* Number of bytes of data to be bound */
  void (*xDel)(void*),   /* Destructor for the data */
  u8 encoding            /* Encoding for the data */
){
  Vdbe *p = (Vdbe *)pStmt;
  Mem *pVar;
  int rc;

  rc = vdbeUnbind(p, i);
  if( rc==SQLITE_OK ){
    if( zData!=0 ){
      pVar = &p->aVar[i-1];
      rc = sqlite3VdbeMemSetStr(pVar, zData, nData, encoding, xDel);
      if( rc==SQLITE_OK && encoding!=0 ){
        rc = sqlite3VdbeChangeEncoding(pVar, ENC(p->db));
      }
      if( rc ){
        sqlite3Error(p->db, rc);
        rc = sqlite3ApiExit(p->db, rc);
      }
    }
    sqlite3_mutex_leave(p->db->mutex);
  }else if( xDel!=SQLITE_STATIC && xDel!=SQLITE_TRANSIENT ){
    xDel((void*)zData);
  }
  return rc;
}
