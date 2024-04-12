static int balance_deeper(MemPage *pRoot, MemPage **ppChild){
  int rc;                        /* Return value from subprocedures */
  MemPage *pChild = 0;           /* Pointer to a new child page */
  Pgno pgnoChild = 0;            /* Page number of the new child page */
  BtShared *pBt = pRoot->pBt;    /* The BTree */

  assert( pRoot->nOverflow>0 );
  assert( sqlite3_mutex_held(pBt->mutex) );

  /* Make pRoot, the root page of the b-tree, writable. Allocate a new
  ** page that will become the new right-child of pPage. Copy the contents
  ** of the node stored on pRoot into the new child page.
  */
  rc = sqlite3PagerWrite(pRoot->pDbPage);
  if( rc==SQLITE_OK ){
    rc = allocateBtreePage(pBt,&pChild,&pgnoChild,pRoot->pgno,0);
    copyNodeContent(pRoot, pChild, &rc);
    if( ISAUTOVACUUM ){
      ptrmapPut(pBt, pgnoChild, PTRMAP_BTREE, pRoot->pgno, &rc);
    }
  }
  if( rc ){
    *ppChild = 0;
    releasePage(pChild);
    return rc;
  }
  assert( sqlite3PagerIswriteable(pChild->pDbPage) );
  assert( sqlite3PagerIswriteable(pRoot->pDbPage) );
  assert( pChild->nCell==pRoot->nCell );

  TRACE(("BALANCE: copy root %d into %d\n", pRoot->pgno, pChild->pgno));

  /* Copy the overflow cells from pRoot to pChild */
  memcpy(pChild->aiOvfl, pRoot->aiOvfl,
         pRoot->nOverflow*sizeof(pRoot->aiOvfl[0]));
  memcpy(pChild->apOvfl, pRoot->apOvfl,
         pRoot->nOverflow*sizeof(pRoot->apOvfl[0]));
  pChild->nOverflow = pRoot->nOverflow;

  /* Zero the contents of pRoot. Then install pChild as the right-child. */
  zeroPage(pRoot, pChild->aData[0] & ~PTF_LEAF);
  put4byte(&pRoot->aData[pRoot->hdrOffset+8], pgnoChild);

  *ppChild = pChild;
  return SQLITE_OK;
}
