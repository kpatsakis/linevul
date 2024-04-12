static void checkAppendMsg(
  IntegrityCk *pCheck,
  const char *zFormat,
  ...
){
  va_list ap;
  if( !pCheck->mxErr ) return;
  pCheck->mxErr--;
  pCheck->nErr++;
  va_start(ap, zFormat);
  if( pCheck->errMsg.nChar ){
    sqlite3StrAccumAppend(&pCheck->errMsg, "\n", 1);
  }
  if( pCheck->zPfx ){
    sqlite3XPrintf(&pCheck->errMsg, pCheck->zPfx, pCheck->v1, pCheck->v2);
  }
  sqlite3VXPrintf(&pCheck->errMsg, zFormat, ap);
  va_end(ap);
  if( pCheck->errMsg.accError==STRACCUM_NOMEM ){
    pCheck->mallocFailed = 1;
  }
}
