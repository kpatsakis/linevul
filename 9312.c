png_get_filter_type(png_structp png_ptr, png_infop info_ptr)
{
   if (png_ptr != NULL && info_ptr != NULL)
      return info_ptr->filter_type;

   return (0);
}
