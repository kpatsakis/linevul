static int countValidCursors(BtShared *pBt, int wrOnly){
  BtCursor *pCur;
  int r = 0;
  for(pCur=pBt->pCursor; pCur; pCur=pCur->pNext){
    if( (wrOnly==0 || (pCur->curFlags & BTCF_WriteFlag)!=0)
     && pCur->eState!=CURSOR_FAULT ) r++; 
  }
  return r;
}
