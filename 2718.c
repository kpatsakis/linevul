  TT_Goto_CodeRange( TT_ExecContext  exec,
                     FT_Int          range,
                     FT_Long         IP )
  {
    TT_CodeRange*  coderange;


    FT_ASSERT( range >= 1 && range <= 3 );

    coderange = &exec->codeRangeTable[range - 1];

    FT_ASSERT( coderange->base != NULL );

    /* NOTE: Because the last instruction of a program may be a CALL */
    /*       which will return to the first byte *after* the code    */
    /*       range, we test for IP <= Size instead of IP < Size.     */
    /*                                                               */
    FT_ASSERT( (FT_ULong)IP <= coderange->size );

    exec->code     = coderange->base;
    exec->codeSize = coderange->size;
    exec->IP       = IP;
    exec->curRange = range;

    return TT_Err_Ok;
  }
