static void callCollNeeded(sqlite3 *db, int enc, const char *zName){
  assert( !db->xCollNeeded || !db->xCollNeeded16 );
  if( db->xCollNeeded ){
    char *zExternal = sqlite3DbStrDup(db, zName);
    if( !zExternal ) return;
    db->xCollNeeded(db->pCollNeededArg, db, enc, zExternal);
    sqlite3DbFree(db, zExternal);
  }
#ifndef SQLITE_OMIT_UTF16
  if( db->xCollNeeded16 ){
    char const *zExternal;
    sqlite3_value *pTmp = sqlite3ValueNew(db);
    sqlite3ValueSetStr(pTmp, -1, zName, SQLITE_UTF8, SQLITE_STATIC);
    zExternal = sqlite3ValueText(pTmp, SQLITE_UTF16NATIVE);
    if( zExternal ){
      db->xCollNeeded16(db->pCollNeededArg, db, (int)ENC(db), zExternal);
    }
    sqlite3ValueFree(pTmp);
  }
#endif
}
