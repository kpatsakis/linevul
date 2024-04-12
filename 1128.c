  cff_decoder_init( CFF_Decoder*    decoder,
                    TT_Face         face,
                    CFF_Size        size,
                    CFF_GlyphSlot   slot,
                    FT_Bool         hinting,
                    FT_Render_Mode  hint_mode )
  {
    CFF_Font  cff = (CFF_Font)face->extra.data;


    /* clear everything */
    FT_MEM_ZERO( decoder, sizeof ( *decoder ) );

    /* initialize builder */
    cff_builder_init( &decoder->builder, face, size, slot, hinting );

    /* initialize Type2 decoder */
    decoder->cff          = cff;
    decoder->num_globals  = cff->global_subrs_index.count;
    decoder->globals      = cff->global_subrs;
    decoder->globals_bias = cff_compute_bias(
                              cff->top_font.font_dict.charstring_type,
                              decoder->num_globals );

    decoder->hint_mode    = hint_mode;
  }
