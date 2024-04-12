ft_bitmap_draw( FT_Bitmap*       bitmap,
                int              x,
                int              y,
                FTDemo_Display*  display,
                grColor          color)
{
  grBitmap  gbit;

  gbit.width  = bitmap->width;
  gbit.rows   = bitmap->rows;
  gbit.pitch  = bitmap->pitch;
  gbit.buffer = bitmap->buffer;

  switch ( bitmap->pixel_mode)
  {
    case FT_PIXEL_MODE_GRAY:
      gbit.mode  = gr_pixel_mode_gray;
      gbit.grays = 256;
      break;

    case FT_PIXEL_MODE_MONO:
      gbit.mode  = gr_pixel_mode_mono;
      gbit.grays = 2;
      break;

    case FT_PIXEL_MODE_LCD:
      gbit.mode  = gr_pixel_mode_lcd;
      gbit.grays = 256;
      break;

    case FT_PIXEL_MODE_LCD_V:
      gbit.mode  = gr_pixel_mode_lcdv;
      gbit.grays = 256;
      break;

    default:
      return;
  }
  grBlitGlyphToBitmap( display->bitmap, &gbit, x, y, color );
}
