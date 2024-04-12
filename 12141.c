png_set_compression_window_bits(png_structp png_ptr, int window_bits)
{
   if (png_ptr == NULL)
      return;
   if (window_bits > 15)
      png_warning(png_ptr, "Only compression windows <= 32k supported by PNG");
   else if (window_bits < 8)
      png_warning(png_ptr, "Only compression windows >= 256 supported by PNG");
#ifndef WBITS_8_OK
   /* Avoid libpng bug with 256-byte windows */
   if (window_bits == 8)
     {
       png_warning(png_ptr, "Compression window is being reset to 512");
       window_bits = 9;
     }
#endif
   png_ptr->flags |= PNG_FLAG_ZLIB_CUSTOM_WINDOW_BITS;
   png_ptr->zlib_window_bits = window_bits;
}
