static int collationMatch(const char *zColl, Index *pIndex){
  int i;
  assert( zColl!=0 );
  for(i=0; i<pIndex->nColumn; i++){
    const char *z = pIndex->azColl[i];
    assert( z!=0 || pIndex->aiColumn[i]<0 );
    if( pIndex->aiColumn[i]>=0 && 0==sqlite3StrICmp(z, zColl) ){
      return 1;
    }
  }
  return 0;
}
