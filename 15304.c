  event_render_mode_change( int  delta )
  {

    if ( delta )
    {
      status.render_mode = ( status.render_mode + delta ) % N_RENDER_MODES;

      if ( status.render_mode < 0 )
        status.render_mode += N_RENDER_MODES;
    }

    switch ( status.render_mode )
    {
    case RENDER_MODE_ALL:
      status.header = (char *)"rendering all glyphs in font";
      break;
    case RENDER_MODE_EMBOLDEN:
      status.header = (char *)"rendering emboldened text";
      break;
    case RENDER_MODE_SLANTED:
      status.header = (char *)"rendering slanted text";
      break;
    case RENDER_MODE_STROKE:
      status.header = (char *)"rendering stroked text";
      break;
    case RENDER_MODE_TEXT:
      status.header = (char *)"rendering test text string";
      break;
    case RENDER_MODE_WATERFALL:
      status.header = (char *)"rendering glyph waterfall";
      break;
    }
  }
