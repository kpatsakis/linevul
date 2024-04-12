static void blobGrowBuffer(Blob *pBlob, int nMin, int *pRc){
  if( *pRc==SQLITE_OK && nMin>pBlob->nAlloc ){
    int nAlloc = nMin;
    char *a = (char *)sqlite3_realloc(pBlob->a, nAlloc);
    if( a ){
      pBlob->nAlloc = nAlloc;
      pBlob->a = a;
    }else{
      *pRc = SQLITE_NOMEM;
    }
  }
}
