static int codeTriggerProgram(
  Parse *pParse,            /* The parser context */
  TriggerStep *pStepList,   /* List of statements inside the trigger body */
  int orconf                /* Conflict algorithm. (OE_Abort, etc) */  
){
  TriggerStep *pStep;
  Vdbe *v = pParse->pVdbe;
  sqlite3 *db = pParse->db;

  assert( pParse->pTriggerTab && pParse->pToplevel );
  assert( pStepList );
  assert( v!=0 );
  for(pStep=pStepList; pStep; pStep=pStep->pNext){
    /* Figure out the ON CONFLICT policy that will be used for this step
    ** of the trigger program. If the statement that caused this trigger
    ** to fire had an explicit ON CONFLICT, then use it. Otherwise, use
    ** the ON CONFLICT policy that was specified as part of the trigger
    ** step statement. Example:
    **
    **   CREATE TRIGGER AFTER INSERT ON t1 BEGIN;
    **     INSERT OR REPLACE INTO t2 VALUES(new.a, new.b);
    **   END;
    **
    **   INSERT INTO t1 ... ;            -- insert into t2 uses REPLACE policy
    **   INSERT OR IGNORE INTO t1 ... ;  -- insert into t2 uses IGNORE policy
    */
    pParse->eOrconf = (orconf==OE_Default)?pStep->orconf:(u8)orconf;
    assert( pParse->okConstFactor==0 );

    switch( pStep->op ){
      case TK_UPDATE: {
        sqlite3Update(pParse, 
          targetSrcList(pParse, pStep),
          sqlite3ExprListDup(db, pStep->pExprList, 0), 
          sqlite3ExprDup(db, pStep->pWhere, 0), 
          pParse->eOrconf
        );
        break;
      }
      case TK_INSERT: {
        sqlite3Insert(pParse, 
          targetSrcList(pParse, pStep),
          sqlite3SelectDup(db, pStep->pSelect, 0), 
          sqlite3IdListDup(db, pStep->pIdList), 
          pParse->eOrconf
        );
        break;
      }
      case TK_DELETE: {
        sqlite3DeleteFrom(pParse, 
          targetSrcList(pParse, pStep),
          sqlite3ExprDup(db, pStep->pWhere, 0)
        );
        break;
      }
      default: assert( pStep->op==TK_SELECT ); {
        SelectDest sDest;
        Select *pSelect = sqlite3SelectDup(db, pStep->pSelect, 0);
        sqlite3SelectDestInit(&sDest, SRT_Discard, 0);
        sqlite3Select(pParse, pSelect, &sDest);
        sqlite3SelectDelete(db, pSelect);
        break;
      }
    } 
    if( pStep->op!=TK_SELECT ){
      sqlite3VdbeAddOp0(v, OP_ResetCount);
    }
  }

  return 0;
}
