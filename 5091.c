static void clearSelect(sqlite3 *db, Select *p, int bFree){
  while( p ){
    Select *pPrior = p->pPrior;
    sqlite3ExprListDelete(db, p->pEList);
    sqlite3SrcListDelete(db, p->pSrc);
    sqlite3ExprDelete(db, p->pWhere);
    sqlite3ExprListDelete(db, p->pGroupBy);
    sqlite3ExprDelete(db, p->pHaving);
    sqlite3ExprListDelete(db, p->pOrderBy);
    sqlite3ExprDelete(db, p->pLimit);
    sqlite3ExprDelete(db, p->pOffset);
    if( p->pWith ) sqlite3WithDelete(db, p->pWith);
    if( bFree ) sqlite3DbFree(db, p);
    p = pPrior;
    bFree = 1;
  }
}
