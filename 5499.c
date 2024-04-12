png_start_read_image(png_structp png_ptr)
{
   png_debug(1, "in png_start_read_image");
 
   if (png_ptr == NULL)
      return;
   if (!(png_ptr->flags & PNG_FLAG_ROW_INIT))
      png_read_start_row(png_ptr);
}
