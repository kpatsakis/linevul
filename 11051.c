png_set_sRGB(png_structp png_ptr, png_infop info_ptr, int intent)
{
   png_debug1(1, "in %s storage function", "sRGB");

   if (png_ptr == NULL || info_ptr == NULL)
      return;

   info_ptr->srgb_intent = (png_byte)intent;
   info_ptr->valid |= PNG_INFO_sRGB;
}
