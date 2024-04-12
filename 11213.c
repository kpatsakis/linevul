static void cacheEntryClear(Parse *pParse, int i){
  if( pParse->aColCache[i].tempReg ){
    if( pParse->nTempReg<ArraySize(pParse->aTempReg) ){
      pParse->aTempReg[pParse->nTempReg++] = pParse->aColCache[i].iReg;
    }
  }
  pParse->nColCache--;
  if( i<pParse->nColCache ){
    pParse->aColCache[i] = pParse->aColCache[pParse->nColCache];
  }
}
