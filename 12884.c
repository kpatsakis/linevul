static int btreeInitPage(MemPage *pPage){

  assert( pPage->pBt!=0 );
  assert( pPage->pBt->db!=0 );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  assert( pPage->pgno==sqlite3PagerPagenumber(pPage->pDbPage) );
  assert( pPage == sqlite3PagerGetExtra(pPage->pDbPage) );
  assert( pPage->aData == sqlite3PagerGetData(pPage->pDbPage) );

  if( !pPage->isInit ){
    int pc;            /* Address of a freeblock within pPage->aData[] */
    u8 hdr;            /* Offset to beginning of page header */
    u8 *data;          /* Equal to pPage->aData */
    BtShared *pBt;        /* The main btree structure */
    int usableSize;    /* Amount of usable space on each page */
    u16 cellOffset;    /* Offset from start of page to first cell pointer */
    int nFree;         /* Number of unused bytes on the page */
    int top;           /* First byte of the cell content area */
    int iCellFirst;    /* First allowable cell or freeblock offset */
    int iCellLast;     /* Last possible cell or freeblock offset */

    pBt = pPage->pBt;

    hdr = pPage->hdrOffset;
    data = pPage->aData;
    /* EVIDENCE-OF: R-28594-02890 The one-byte flag at offset 0 indicating
    ** the b-tree page type. */
    if( decodeFlags(pPage, data[hdr]) ) return SQLITE_CORRUPT_BKPT;
    assert( pBt->pageSize>=512 && pBt->pageSize<=65536 );
    pPage->maskPage = (u16)(pBt->pageSize - 1);
    pPage->nOverflow = 0;
    usableSize = pBt->usableSize;
    pPage->cellOffset = cellOffset = hdr + 8 + pPage->childPtrSize;
    pPage->aDataEnd = &data[usableSize];
    pPage->aCellIdx = &data[cellOffset];
    pPage->aDataOfst = &data[pPage->childPtrSize];
    /* EVIDENCE-OF: R-58015-48175 The two-byte integer at offset 5 designates
    ** the start of the cell content area. A zero value for this integer is
    ** interpreted as 65536. */
    top = get2byteNotZero(&data[hdr+5]);
    /* EVIDENCE-OF: R-37002-32774 The two-byte integer at offset 3 gives the
    ** number of cells on the page. */
    pPage->nCell = get2byte(&data[hdr+3]);
    if( pPage->nCell>MX_CELL(pBt) ){
      /* To many cells for a single page.  The page must be corrupt */
      return SQLITE_CORRUPT_BKPT;
    }
    testcase( pPage->nCell==MX_CELL(pBt) );
    /* EVIDENCE-OF: R-24089-57979 If a page contains no cells (which is only
    ** possible for a root page of a table that contains no rows) then the
    ** offset to the cell content area will equal the page size minus the
    ** bytes of reserved space. */
    assert( pPage->nCell>0 || top==usableSize || CORRUPT_DB );

    /* A malformed database page might cause us to read past the end
    ** of page when parsing a cell.  
    **
    ** The following block of code checks early to see if a cell extends
    ** past the end of a page boundary and causes SQLITE_CORRUPT to be 
    ** returned if it does.
    */
    iCellFirst = cellOffset + 2*pPage->nCell;
    iCellLast = usableSize - 4;
    if( pBt->db->flags & SQLITE_CellSizeCk ){
      int i;            /* Index into the cell pointer array */
      int sz;           /* Size of a cell */

      if( !pPage->leaf ) iCellLast--;
      for(i=0; i<pPage->nCell; i++){
        pc = get2byteAligned(&data[cellOffset+i*2]);
        testcase( pc==iCellFirst );
        testcase( pc==iCellLast );
        if( pc<iCellFirst || pc>iCellLast ){
          return SQLITE_CORRUPT_BKPT;
        }
        sz = pPage->xCellSize(pPage, &data[pc]);
        testcase( pc+sz==usableSize );
        if( pc+sz>usableSize ){
          return SQLITE_CORRUPT_BKPT;
        }
      }
      if( !pPage->leaf ) iCellLast++;
    }  

    /* Compute the total free space on the page
    ** EVIDENCE-OF: R-23588-34450 The two-byte integer at offset 1 gives the
    ** start of the first freeblock on the page, or is zero if there are no
    ** freeblocks. */
    pc = get2byte(&data[hdr+1]);
    nFree = data[hdr+7] + top;  /* Init nFree to non-freeblock free space */
    if( pc>0 ){
      u32 next, size;
      if( pc<iCellFirst ){
        /* EVIDENCE-OF: R-55530-52930 In a well-formed b-tree page, there will
        ** always be at least one cell before the first freeblock.
        */
        return SQLITE_CORRUPT_BKPT; 
      }
      while( 1 ){
        if( pc>iCellLast ){
          return SQLITE_CORRUPT_BKPT; /* Freeblock off the end of the page */
        }
        next = get2byte(&data[pc]);
        size = get2byte(&data[pc+2]);
        nFree = nFree + size;
        if( next<=pc+size+3 ) break;
        pc = next;
      }
      if( next>0 ){
        return SQLITE_CORRUPT_BKPT;  /* Freeblock not in ascending order */
      }
      if( pc+size>(unsigned int)usableSize ){
        return SQLITE_CORRUPT_BKPT;  /* Last freeblock extends past page end */
      }
    }

    /* At this point, nFree contains the sum of the offset to the start
    ** of the cell-content area plus the number of free bytes within
    ** the cell-content area. If this is greater than the usable-size
    ** of the page, then the page must be corrupted. This check also
    ** serves to verify that the offset to the start of the cell-content
    ** area, according to the page header, lies within the page.
    */
    if( nFree>usableSize ){
      return SQLITE_CORRUPT_BKPT; 
    }
    pPage->nFree = (u16)(nFree - iCellFirst);
    pPage->isInit = 1;
  }
  return SQLITE_OK;
}
