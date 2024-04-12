png_set_flush(png_structp png_ptr, int nrows)
{
   png_debug(1, "in png_set_flush");

   if (png_ptr == NULL)
      return;
   png_ptr->flush_dist = (nrows < 0 ? 0 : nrows);
}
