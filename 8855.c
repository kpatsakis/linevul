  find_unicode_charmap( FT_Face  face )
  {
    FT_CharMap*  first;
    FT_CharMap*  cur;


    /* caller should have already checked that `face' is valid */
    FT_ASSERT( face );

    first = face->charmaps;

    if ( !first )
      return FT_Err_Invalid_CharMap_Handle;

    /*
     *  The original TrueType specification(s) only specified charmap
     *  formats that are capable of mapping 8 or 16 bit character codes to
     *  glyph indices.
     *
     *  However, recent updates to the Apple and OpenType specifications
     *  introduced new formats that are capable of mapping 32-bit character
     *  codes as well.  And these are already used on some fonts, mainly to
     *  map non-BMP Asian ideographs as defined in Unicode.
     *
     *  For compatibility purposes, these fonts generally come with
     *  *several* Unicode charmaps:
     *
     *   - One of them in the "old" 16-bit format, that cannot access
     *     all glyphs in the font.
     *
     *   - Another one in the "new" 32-bit format, that can access all
     *     the glyphs.
     *
     *  This function has been written to always favor a 32-bit charmap
     *  when found.  Otherwise, a 16-bit one is returned when found.
     */

    /* Since the `interesting' table, with IDs (3,10), is normally the */
    /* last one, we loop backwards.  This loses with type1 fonts with  */
    /* non-BMP characters (<.0001%), this wins with .ttf with non-BMP  */
    /* chars (.01% ?), and this is the same about 99.99% of the time!  */

    cur = first + face->num_charmaps;  /* points after the last one */

    for ( ; --cur >= first; )
    {
      if ( cur[0]->encoding == FT_ENCODING_UNICODE )
      {
        /* XXX If some new encodings to represent UCS-4 are added, */
        /*     they should be added here.                          */
        if ( ( cur[0]->platform_id == TT_PLATFORM_MICROSOFT &&
               cur[0]->encoding_id == TT_MS_ID_UCS_4        )     ||
             ( cur[0]->platform_id == TT_PLATFORM_APPLE_UNICODE &&
               cur[0]->encoding_id == TT_APPLE_ID_UNICODE_32    ) )
        {
#ifdef FT_MAX_CHARMAP_CACHEABLE
          if ( cur - first > FT_MAX_CHARMAP_CACHEABLE )
          {
            FT_ERROR(( "find_unicode_charmap: UCS-4 cmap is found "
                       "at too late position (%d)\n", cur - first ));
            continue;
          }
#endif
          face->charmap = cur[0];
          return FT_Err_Ok;
        }
      }
    }

    /* We do not have any UCS-4 charmap.                */
    /* Do the loop again and search for UCS-2 charmaps. */
    cur = first + face->num_charmaps;

    for ( ; --cur >= first; )
    {
      if ( cur[0]->encoding == FT_ENCODING_UNICODE )
      {
#ifdef FT_MAX_CHARMAP_CACHEABLE
        if ( cur - first > FT_MAX_CHARMAP_CACHEABLE )
        {
          FT_ERROR(( "find_unicode_charmap: UCS-2 cmap is found "
                     "at too late position (%d)\n", cur - first ));
          continue;
        }
#endif
        face->charmap = cur[0];
        return FT_Err_Ok;
      }
    }

    return FT_Err_Invalid_CharMap_Handle;
  }
