png_set_sCAL(png_structp png_ptr, png_infop info_ptr,
             int unit, double width, double height)
{
   png_debug1(1, "in %s storage function", "sCAL");

   if (png_ptr == NULL || info_ptr == NULL)
      return;

   info_ptr->scal_unit = (png_byte)unit;
   info_ptr->scal_pixel_width = width;
   info_ptr->scal_pixel_height = height;

   info_ptr->valid |= PNG_INFO_sCAL;
}
