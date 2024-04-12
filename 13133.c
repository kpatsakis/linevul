  tt_cmap0_char_next( TT_CMap     cmap,
                      FT_UInt32  *pchar_code )
  {
    FT_Byte*   table    = cmap->data;
    FT_UInt32  charcode = *pchar_code;
    FT_UInt32  result   = 0;
    FT_UInt    gindex   = 0;


    table += 6;  /* go to glyph IDs */
    while ( ++charcode < 256 )
    {
      gindex = table[charcode];
      if ( gindex != 0 )
      {
        result = charcode;
        break;
      }
    }

    *pchar_code = result;
    return gindex;
  }
