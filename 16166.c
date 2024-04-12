static int decodeFlags(MemPage *pPage, int flagByte){
  BtShared *pBt;     /* A copy of pPage->pBt */

  assert( pPage->hdrOffset==(pPage->pgno==1 ? 100 : 0) );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  pPage->leaf = (u8)(flagByte>>3);  assert( PTF_LEAF == 1<<3 );
  flagByte &= ~PTF_LEAF;
  pPage->childPtrSize = 4-4*pPage->leaf;
  pPage->xCellSize = cellSizePtr;
  pBt = pPage->pBt;
  if( flagByte==(PTF_LEAFDATA | PTF_INTKEY) ){
    /* EVIDENCE-OF: R-07291-35328 A value of 5 (0x05) means the page is an
    ** interior table b-tree page. */
    assert( (PTF_LEAFDATA|PTF_INTKEY)==5 );
    /* EVIDENCE-OF: R-26900-09176 A value of 13 (0x0d) means the page is a
    ** leaf table b-tree page. */
    assert( (PTF_LEAFDATA|PTF_INTKEY|PTF_LEAF)==13 );
    pPage->intKey = 1;
    if( pPage->leaf ){
      pPage->intKeyLeaf = 1;
      pPage->xParseCell = btreeParseCellPtr;
    }else{
      pPage->intKeyLeaf = 0;
      pPage->xCellSize = cellSizePtrNoPayload;
      pPage->xParseCell = btreeParseCellPtrNoPayload;
    }
    pPage->maxLocal = pBt->maxLeaf;
    pPage->minLocal = pBt->minLeaf;
  }else if( flagByte==PTF_ZERODATA ){
    /* EVIDENCE-OF: R-43316-37308 A value of 2 (0x02) means the page is an
    ** interior index b-tree page. */
    assert( (PTF_ZERODATA)==2 );
    /* EVIDENCE-OF: R-59615-42828 A value of 10 (0x0a) means the page is a
    ** leaf index b-tree page. */
    assert( (PTF_ZERODATA|PTF_LEAF)==10 );
    pPage->intKey = 0;
    pPage->intKeyLeaf = 0;
    pPage->xParseCell = btreeParseCellPtrIndex;
    pPage->maxLocal = pBt->maxLocal;
    pPage->minLocal = pBt->minLocal;
  }else{
    /* EVIDENCE-OF: R-47608-56469 Any other value for the b-tree page type is
    ** an error. */
    return SQLITE_CORRUPT_BKPT;
  }
  pPage->max1bytePayload = pBt->max1bytePayload;
  return SQLITE_OK;
}
