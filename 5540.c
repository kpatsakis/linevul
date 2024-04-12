png_get_oFFs(png_structp png_ptr, png_infop info_ptr,
   png_int_32 *offset_x, png_int_32 *offset_y, int *unit_type)
{
   png_debug1(1, "in %s retrieval function", "oFFs");

   if (png_ptr != NULL && info_ptr != NULL && (info_ptr->valid & PNG_INFO_oFFs)
      && offset_x != NULL && offset_y != NULL && unit_type != NULL)
   {
      *offset_x = info_ptr->x_offset;
      *offset_y = info_ptr->y_offset;
      *unit_type = (int)info_ptr->offset_unit_type;
      return (PNG_INFO_oFFs);
   }
   return (0);
}
