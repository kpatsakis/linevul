  cff_fd_select_get( CFF_FDSelect  fdselect,
                     FT_UInt       glyph_index )
  {
    FT_Byte  fd = 0;


    switch ( fdselect->format )
    {
    case 0:
      fd = fdselect->data[glyph_index];
      break;

    case 3:
      /* first, compare to cache */
      if ( (FT_UInt)( glyph_index - fdselect->cache_first ) <
                        fdselect->cache_count )
      {
        fd = fdselect->cache_fd;
        break;
      }

      /* then, lookup the ranges array */
      {
        FT_Byte*  p       = fdselect->data;
        FT_Byte*  p_limit = p + fdselect->data_size;
        FT_Byte   fd2;
        FT_UInt   first, limit;


        first = FT_NEXT_USHORT( p );
        do
        {
          if ( glyph_index < first )
            break;

          fd2   = *p++;
          limit = FT_NEXT_USHORT( p );

          if ( glyph_index < limit )
          {
            fd = fd2;

            /* update cache */
            fdselect->cache_first = first;
            fdselect->cache_count = limit-first;
            fdselect->cache_fd    = fd2;
            break;
          }
          first = limit;

        } while ( p < p_limit );
      }
      break;

    default:
      ;
    }

    return fd;
  }
