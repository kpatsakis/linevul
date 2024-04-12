  tt_sbit_decoder_load_bit_aligned( TT_SBitDecoder  decoder,
                                    FT_Byte*        p,
                                    FT_Byte*        limit,
                                    FT_Int          x_pos,
                                    FT_Int          y_pos )
  {
    FT_Error    error = FT_Err_Ok;
    FT_Byte*    line;
    FT_Int      bit_height, bit_width, pitch, width, height, line_bits, h, nbits;
    FT_Bitmap*  bitmap;
    FT_UShort   rval;


    /* check that we can write the glyph into the bitmap */
    bitmap     = decoder->bitmap;
    bit_width  = bitmap->width;
    bit_height = bitmap->rows;
    pitch      = bitmap->pitch;
    line       = bitmap->buffer;

    width  = decoder->metrics->width;
    height = decoder->metrics->height;

    line_bits = width * decoder->bit_depth;

    if ( x_pos < 0 || x_pos + width  > bit_width  ||
         y_pos < 0 || y_pos + height > bit_height )
    {
      FT_TRACE1(( "tt_sbit_decoder_load_bit_aligned:"
                  " invalid bitmap dimensions\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Exit;
    }

    if ( p + ( ( line_bits * height + 7 ) >> 3 ) > limit )
    {
      FT_TRACE1(( "tt_sbit_decoder_load_bit_aligned: broken bitmap\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Exit;
    }

    /* now do the blit */

    /* adjust `line' to point to the first byte of the bitmap */
    line  += y_pos * pitch + ( x_pos >> 3 );
    x_pos &= 7;

    /* the higher byte of `rval' is used as a buffer */
    rval  = 0;
    nbits = 0;

    for ( h = height; h > 0; h--, line += pitch )
    {
      FT_Byte*  pwrite = line;
      FT_Int    w      = line_bits;


      /* handle initial byte (in target bitmap) specially if necessary */
      if ( x_pos )
      {
        w = ( line_bits < 8 - x_pos ) ? line_bits : 8 - x_pos;

        if ( h == height )
        {
          rval  = *p++;
          nbits = x_pos;
        }
        else if ( nbits < w )
        {
          if ( p < limit )
            rval |= *p++;
          nbits += 8 - w;
        }
        else
        {
          rval  >>= 8;
          nbits  -= w;
        }

        *pwrite++ |= ( ( rval >> nbits ) & 0xFF ) &
                     ( ~( 0xFF << w ) << ( 8 - w - x_pos ) );
        rval     <<= 8;

        w = line_bits - w;
      }

      /* handle medial bytes */
      for ( ; w >= 8; w -= 8 )
      {
        rval      |= *p++;
        *pwrite++ |= ( rval >> nbits ) & 0xFF;

        rval <<= 8;
      }

      /* handle final byte if necessary */
      if ( w > 0 )
      {
        if ( nbits < w )
        {
          if ( p < limit )
            rval |= *p++;
          *pwrite |= ( ( rval >> nbits ) & 0xFF ) & ( 0xFF00U >> w );
          nbits   += 8 - w;

          rval <<= 8;
        }
        else
        {
          *pwrite |= ( ( rval >> nbits ) & 0xFF ) & ( 0xFF00U >> w );
          nbits   -= w;
        }
      }
    }

  Exit:
    if ( !error )
      FT_TRACE3(( "tt_sbit_decoder_load_bit_aligned: loaded\n" ));
    return error;
  }
