static int dbpageBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  int i;
  int iPlan = 0;

  /* If there is a schema= constraint, it must be honored.  Report a
  ** ridiculously large estimated cost if the schema= constraint is
  ** unavailable
  */
  for(i=0; i<pIdxInfo->nConstraint; i++){
    struct sqlite3_index_constraint *p = &pIdxInfo->aConstraint[i];
    if( p->iColumn!=DBPAGE_COLUMN_SCHEMA ) continue;
    if( p->op!=SQLITE_INDEX_CONSTRAINT_EQ ) continue;
    if( !p->usable ){
      /* No solution. */
      return SQLITE_CONSTRAINT;
    }
    iPlan = 2;
    pIdxInfo->aConstraintUsage[i].argvIndex = 1;
    pIdxInfo->aConstraintUsage[i].omit = 1;
    break;
  }

  /* If we reach this point, it means that either there is no schema=
  ** constraint (in which case we use the "main" schema) or else the
  ** schema constraint was accepted.  Lower the estimated cost accordingly
  */
  pIdxInfo->estimatedCost = 1.0e6;

  /* Check for constraints against pgno */
  for(i=0; i<pIdxInfo->nConstraint; i++){
    struct sqlite3_index_constraint *p = &pIdxInfo->aConstraint[i];
    if( p->usable && p->iColumn<=0 && p->op==SQLITE_INDEX_CONSTRAINT_EQ ){
      pIdxInfo->estimatedRows = 1;
      pIdxInfo->idxFlags = SQLITE_INDEX_SCAN_UNIQUE;
      pIdxInfo->estimatedCost = 1.0;
      pIdxInfo->aConstraintUsage[i].argvIndex = iPlan ? 2 : 1;
      pIdxInfo->aConstraintUsage[i].omit = 1;
      iPlan |= 1;
      break;
    }
  }
  pIdxInfo->idxNum = iPlan;

  if( pIdxInfo->nOrderBy>=1
   && pIdxInfo->aOrderBy[0].iColumn<=0
   && pIdxInfo->aOrderBy[0].desc==0
  ){
    pIdxInfo->orderByConsumed = 1;
  }
  return SQLITE_OK;
}
