  tt_cmap12_init( TT_CMap12  cmap,
                  FT_Byte*   table )
  {
    cmap->cmap.data  = table;

    table           += 12;
    cmap->num_groups = FT_PEEK_ULONG( table );

    cmap->valid      = 0;

    return SFNT_Err_Ok;
  }
