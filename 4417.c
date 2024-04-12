png_read_update_info(png_structp png_ptr, png_infop info_ptr)
{
   png_debug(1, "in png_read_update_info");
 
   if (png_ptr == NULL)
      return;
   if (!(png_ptr->flags & PNG_FLAG_ROW_INIT))
      png_read_start_row(png_ptr);
   else
      png_warning(png_ptr,
      "Ignoring extra png_read_update_info() call; row buffer not reallocated");

   png_read_transform_info(png_ptr, info_ptr);
}
