  render_state_draw( RenderState           state,
                     const unsigned char*  text,
                     int                   idx,
                     int                   x,
                     int                   y,
                     int                   width,
                     int                   height )
  {
    ColumnState           column         = &state->columns[idx];
    const unsigned char*  p              = text;
    long                  load_flags     = FT_LOAD_DEFAULT;
    FT_Face               face           = state->face;
    int                   left           = x;
    int                   right          = x + width;
    int                   bottom         = y + height;
    int                   line_height;
    FT_UInt               prev_glyph     = 0;
    FT_Pos                prev_rsb_delta = 0;
    FT_Pos                x_origin       = x << 6;
    HintMode              rmode          = column->hint_mode;


    if ( !face )
      return;

    _render_state_rescale( state );

    if ( column->use_lcd_filter )
      FT_Library_SetLcdFilter( face->glyph->library, column->lcd_filter );

    if ( column->use_custom_lcd_filter )
      FT_Library_SetLcdFilterWeights( face->glyph->library,
                                      column->filter_weights );

    y          += state->size->metrics.ascender / 64;
    line_height = state->size->metrics.height / 64;

    if ( rmode == HINT_MODE_AUTOHINT )
      load_flags = FT_LOAD_FORCE_AUTOHINT;

    if ( rmode == HINT_MODE_AUTOHINT_LIGHT )
      load_flags = FT_LOAD_TARGET_LIGHT;

    if ( rmode == HINT_MODE_UNHINTED )
      load_flags |= FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP;

    if ( !column->use_global_advance_width )
      load_flags |= FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH;

    for ( ; *p; p++ )
    {
      FT_UInt       gindex;
      FT_Error      error;
      FT_GlyphSlot  slot = face->glyph;
      FT_Bitmap*    map  = &slot->bitmap;
      int           xmax;


      /* handle newlines */
      if ( *p == 0x0A )
      {
        if ( p[1] == 0x0D )
          p++;
        x_origin = left << 6;
        y       += line_height;
        prev_rsb_delta = 0;
        if ( y >= bottom )
          break;
        continue;
      }
      else if ( *p == 0x0D )
      {
        if ( p[1] == 0x0A )
          p++;
        x_origin = left << 6;
        y       += line_height;
        prev_rsb_delta = 0;
        if ( y >= bottom )
          break;
        continue;
      }

      gindex = FT_Get_Char_Index( state->face, p[0] );
      error  = FT_Load_Glyph( face, gindex, load_flags );

      if ( error )
        continue;

      if ( column->use_kerning && gindex != 0 && prev_glyph != 0 )
      {
        FT_Vector  vec;
        FT_Int     kerning_mode = FT_KERNING_DEFAULT;


        if ( rmode == HINT_MODE_UNHINTED )
          kerning_mode = FT_KERNING_UNFITTED;

        FT_Get_Kerning( face, prev_glyph, gindex, kerning_mode, &vec );

        x_origin += vec.x;
      }

      if ( column->use_deltas )
      {
        if ( prev_rsb_delta - face->glyph->lsb_delta >= 32 )
          x_origin -= 64;
        else if ( prev_rsb_delta - face->glyph->lsb_delta < -32 )
          x_origin += 64;
      }
      prev_rsb_delta = face->glyph->rsb_delta;

      /* implement sub-pixel positining for un-hinted mode */
      if ( rmode == HINT_MODE_UNHINTED           &&
           slot->format == FT_GLYPH_FORMAT_OUTLINE )
      {
        FT_Pos  shift = x_origin & 63;


        FT_Outline_Translate( &slot->outline, shift, 0 );
      }

      if ( slot->format == FT_GLYPH_FORMAT_OUTLINE )
      {
        FT_BBox  cbox;


        FT_Outline_Get_CBox( &slot->outline, &cbox );
        xmax = ( x_origin + cbox.xMax + 63 ) >> 6;

        FT_Render_Glyph( slot,
                         column->use_lcd_filter ? FT_RENDER_MODE_LCD
                                                : FT_RENDER_MODE_NORMAL );
      }
      else
        xmax = ( x_origin >> 6 ) + slot->bitmap_left + slot->bitmap.width;

      if ( xmax >= right )
      {
        x  = left;
        y += line_height;
        if ( y >= bottom )
          break;

        x_origin       = x << 6;
        prev_rsb_delta = 0;
      }

      {
        DisplayMode  mode = DISPLAY_MODE_MONO;


        if ( slot->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY )
          mode = DISPLAY_MODE_GRAY;
        else if ( slot->bitmap.pixel_mode == FT_PIXEL_MODE_LCD )
          mode = DISPLAY_MODE_LCD;

        state->display.disp_draw( state->display.disp, mode,
                                  ( x_origin >> 6 ) + slot->bitmap_left,
                                  y - slot->bitmap_top,
                                  map->width, map->rows,
                                  map->pitch, map->buffer );
      }
      if ( rmode == HINT_MODE_UNHINTED )
        x_origin += slot->linearHoriAdvance >> 10;
      else
        x_origin += slot->advance.x;

      prev_glyph = gindex;
    }

    /* display footer on this column */
    {
      void*        disp = state->display.disp;
      const char  *msg;
      char         temp[64];


      msg = render_mode_names[column->hint_mode];
      state->display.disp_text( disp, left, bottom + 5, msg );

      if ( !column->use_lcd_filter )
        msg = "gray rendering";
      else if ( column->use_custom_lcd_filter )
      {
        int             fwi = column->fw_index;
        unsigned char  *fw  = column->filter_weights;


        msg = "";

        sprintf( temp,
                 "%s0x%02X%s0x%02X%s0x%02X%s0x%02X%s0x%02X%s",
                 fwi == 0 ? "[" : " ",
                   fw[0],
                 fwi == 0 ? "]" : ( fwi == 1 ? "[" : " " ),
                   fw[1],
                 fwi == 1 ? "]" : ( fwi == 2 ? "[" : " " ),
                   fw[2],
                 fwi == 2 ? "]" : ( fwi == 3 ? "[" : " " ),
                   fw[3],
                 fwi == 3 ? "]" : ( fwi == 4 ? "[" : " " ),
                   fw[4],
                 fwi == 4 ? "]" : " " );
        state->display.disp_text( disp, left, bottom + 15, temp );
      }
      else switch ( column->lcd_filter )
      {
      case FT_LCD_FILTER_NONE:
        msg = "LCD without filtering";
        break;
      case FT_LCD_FILTER_DEFAULT:
        msg = "default LCD filter";
        break;
      case FT_LCD_FILTER_LIGHT:
        msg = "light LCD filter";
        break;
      default:
        msg = "legacy LCD filter";
      }
      state->display.disp_text( disp, left, bottom + 15, msg );

      sprintf(temp, "%s %s %s",
              column->use_kerning ? "+kern"
                                  : "-kern",
              column->use_deltas ? "+delta"
                                 : "-delta",
              column->use_global_advance_width ? "+advance"
                                               : "-advance" );
      state->display.disp_text( disp, left, bottom + 25, temp );

      if ( state->col == idx )
        state->display.disp_text( disp, left, bottom + 35, "**************" );
    }
  }
