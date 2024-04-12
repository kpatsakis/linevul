  static int cellInfoEqual(CellInfo *a, CellInfo *b){
    if( a->nKey!=b->nKey ) return 0;
    if( a->pPayload!=b->pPayload ) return 0;
    if( a->nPayload!=b->nPayload ) return 0;
    if( a->nLocal!=b->nLocal ) return 0;
    if( a->nSize!=b->nSize ) return 0;
    return 1;
  }
