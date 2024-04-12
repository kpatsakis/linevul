  T42_GlyphSlot_Load( FT_GlyphSlot  glyph,
                      FT_Size       size,
                      FT_UInt       glyph_index,
                      FT_Int32      load_flags )
  {
    FT_Error         error;
    T42_GlyphSlot    t42slot = (T42_GlyphSlot)glyph;
    T42_Size         t42size = (T42_Size)size;
    FT_Driver_Class  ttclazz = ((T42_Driver)glyph->face->driver)->ttclazz;


    FT_TRACE1(( "T42_GlyphSlot_Load: glyph index %d\n", glyph_index ));

    t42_glyphslot_clear( t42slot->ttslot );
    error = ttclazz->load_glyph( t42slot->ttslot,
                                 t42size->ttsize,
                                 glyph_index,
                                 load_flags | FT_LOAD_NO_BITMAP );

    if ( !error )
    {
      glyph->metrics = t42slot->ttslot->metrics;

      glyph->linearHoriAdvance = t42slot->ttslot->linearHoriAdvance;
      glyph->linearVertAdvance = t42slot->ttslot->linearVertAdvance;

      glyph->format  = t42slot->ttslot->format;
      glyph->outline = t42slot->ttslot->outline;

      glyph->bitmap      = t42slot->ttslot->bitmap;
      glyph->bitmap_left = t42slot->ttslot->bitmap_left;
      glyph->bitmap_top  = t42slot->ttslot->bitmap_top;

      glyph->num_subglyphs = t42slot->ttslot->num_subglyphs;
      glyph->subglyphs     = t42slot->ttslot->subglyphs;

      glyph->control_data  = t42slot->ttslot->control_data;
      glyph->control_len   = t42slot->ttslot->control_len;
    }

    return error;
  }
