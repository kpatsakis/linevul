  t42_glyphslot_clear( FT_GlyphSlot  slot )
  {
    /* free bitmap if needed */
    ft_glyphslot_free_bitmap( slot );

    /* clear all public fields in the glyph slot */
    FT_ZERO( &slot->metrics );
    FT_ZERO( &slot->outline );
    FT_ZERO( &slot->bitmap );

    slot->bitmap_left   = 0;
    slot->bitmap_top    = 0;
    slot->num_subglyphs = 0;
    slot->subglyphs     = 0;
    slot->control_data  = 0;
    slot->control_len   = 0;
    slot->other         = 0;
    slot->format        = FT_GLYPH_FORMAT_NONE;

    slot->linearHoriAdvance = 0;
    slot->linearVertAdvance = 0;
  }
