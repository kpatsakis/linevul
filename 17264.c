static void btreeParseCellPtrNoPayload(
  MemPage *pPage,         /* Page containing the cell */
  u8 *pCell,              /* Pointer to the cell text. */
  CellInfo *pInfo         /* Fill in this structure */
){
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  assert( pPage->leaf==0 );
  assert( pPage->childPtrSize==4 );
#ifndef SQLITE_DEBUG
  UNUSED_PARAMETER(pPage);
#endif
  pInfo->nSize = 4 + getVarint(&pCell[4], (u64*)&pInfo->nKey);
  pInfo->nPayload = 0;
  pInfo->nLocal = 0;
  pInfo->pPayload = 0;
  return;
}
