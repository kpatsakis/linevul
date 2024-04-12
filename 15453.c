static void countInverse(sqlite3_context *ctx, int argc, sqlite3_value **argv){
  CountCtx *p;
  p = sqlite3_aggregate_context(ctx, sizeof(*p));
  /* p is always non-NULL since countStep() will have been called first */
  if( (argc==0 || SQLITE_NULL!=sqlite3_value_type(argv[0])) && ALWAYS(p) ){
    p->n--;
#ifdef SQLITE_DEBUG
    p->bInverse = 1;
#endif
  }
}
