png_write_tRNS(png_structp png_ptr, png_bytep trans, png_color_16p tran,
   int num_trans, int color_type)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_tRNS;
#endif
   png_byte buf[6];

   png_debug(1, "in png_write_tRNS");

   if (color_type == PNG_COLOR_TYPE_PALETTE)
   {
      if (num_trans <= 0 || num_trans > (int)png_ptr->num_palette)
      {
         png_warning(png_ptr, "Invalid number of transparent colors specified");
         return;
      }
      /* Write the chunk out as it is */
      png_write_chunk(png_ptr, (png_bytep)png_tRNS, trans,
        (png_size_t)num_trans);
   }
   else if (color_type == PNG_COLOR_TYPE_GRAY)
   {
      /* One 16 bit value */
      if (tran->gray >= (1 << png_ptr->bit_depth))
      {
         png_warning(png_ptr,
           "Ignoring attempt to write tRNS chunk out-of-range for bit_depth");
         return;
      }
      png_save_uint_16(buf, tran->gray);
      png_write_chunk(png_ptr, (png_bytep)png_tRNS, buf, (png_size_t)2);
   }
   else if (color_type == PNG_COLOR_TYPE_RGB)
   {
      /* Three 16 bit values */
      png_save_uint_16(buf, tran->red);
      png_save_uint_16(buf + 2, tran->green);
      png_save_uint_16(buf + 4, tran->blue);
      if (png_ptr->bit_depth == 8 && (buf[0] | buf[2] | buf[4]))
      {
         png_warning(png_ptr,
           "Ignoring attempt to write 16-bit tRNS chunk when bit_depth is 8");
         return;
      }
      png_write_chunk(png_ptr, (png_bytep)png_tRNS, buf, (png_size_t)6);
   }
   else
   {
      png_warning(png_ptr, "Can't write tRNS with an alpha channel");
   }
}
