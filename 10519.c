png_get_signature(png_structp png_ptr, png_infop info_ptr)
{
   if (png_ptr != NULL && info_ptr != NULL)
      return(info_ptr->signature);
   else
      return (NULL);
}
