static HB_Error  Get_Anchor( GPOS_Instance*   gpi,
			     HB_Anchor*      an,
			     HB_UShort        glyph_index,
			     HB_Fixed*          x_value,
			     HB_Fixed*          y_value )
{
  HB_Error  error = HB_Err_Ok;

#ifdef HB_SUPPORT_MULTIPLE_MASTER
  HB_GPOSHeader*  gpos = gpi->gpos;
#endif
  HB_UShort        ap;

  HB_Short         pixel_value;

  HB_UShort        x_ppem, y_ppem;
  HB_16Dot16         x_scale, y_scale;


  x_ppem  = gpi->font->x_ppem;
  y_ppem  = gpi->font->y_ppem;
  x_scale = gpi->font->x_scale;
  y_scale = gpi->font->y_scale;

  switch ( an->PosFormat )
  {
  case 0:
    /* The special case of an empty AnchorTable */
  default:

    return HB_Err_Not_Covered;

  case 1:
    *x_value = x_scale * an->af.af1.XCoordinate / 0x10000;
    *y_value = y_scale * an->af.af1.YCoordinate / 0x10000;
    break;

  case 2:
    if ( !gpi->dvi )
    {
      hb_uint32 n_points = 0;
      ap = an->af.af2.AnchorPoint;
      if (!gpi->font->klass->getPointInOutline)
          goto no_contour_point;
      error = gpi->font->klass->getPointInOutline(gpi->font, glyph_index, gpi->load_flags, ap, x_value, y_value, &n_points);
      if (error)
          return error;
      /* if n_points is set to zero, we use the design coordinate value pair.
       * This can happen e.g. for sbit glyphs. */
      if (!n_points)
          goto no_contour_point;
    }
    else
    {
    no_contour_point:
      *x_value = x_scale * an->af.af3.XCoordinate / 0x10000;
      *y_value = y_scale * an->af.af3.YCoordinate / 0x10000;
    }
    break;

  case 3:
    if ( !gpi->dvi )
    {
      _HB_OPEN_Get_Device( an->af.af3.DeviceTables[AF3_X_DEVICE_TABLE], x_ppem, &pixel_value );
      *x_value = pixel_value << 6;
      _HB_OPEN_Get_Device( an->af.af3.DeviceTables[AF3_Y_DEVICE_TABLE], y_ppem, &pixel_value );
      *y_value = pixel_value << 6;
    }
    else
      *x_value = *y_value = 0;

    *x_value += x_scale * an->af.af3.XCoordinate / 0x10000;
    *y_value += y_scale * an->af.af3.YCoordinate / 0x10000;
    break;

  case 4:
#ifdef HB_SUPPORT_MULTIPLE_MASTER
    error = (gpos->mmfunc)( gpi->font, an->af.af4.XIdAnchor,
			    x_value, gpos->data );
    if ( error )
      return error;

    error = (gpos->mmfunc)( gpi->font, an->af.af4.YIdAnchor,
			    y_value, gpos->data );
    if ( error )
      return error;
    break;
#else
    return ERR(HB_Err_Not_Covered);
#endif
  }

  return error;
}
