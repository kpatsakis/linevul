png_write_IHDR(png_structp png_ptr, png_uint_32 width, png_uint_32 height,
   int bit_depth, int color_type, int compression_type, int filter_type,
   int interlace_type)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_IHDR;
#endif
   int ret;

   png_byte buf[13]; /* Buffer to store the IHDR info */

   png_debug(1, "in png_write_IHDR");

   /* Check that we have valid input data from the application info */
   switch (color_type)
   {
      case PNG_COLOR_TYPE_GRAY:
         switch (bit_depth)
         {
            case 1:
            case 2:
            case 4:
            case 8:
            case 16: png_ptr->channels = 1; break;
            default: png_error(png_ptr,
                         "Invalid bit depth for grayscale image");
         }
         break;
      case PNG_COLOR_TYPE_RGB:
         if (bit_depth != 8 && bit_depth != 16)
            png_error(png_ptr, "Invalid bit depth for RGB image");
         png_ptr->channels = 3;
         break;
      case PNG_COLOR_TYPE_PALETTE:
         switch (bit_depth)
         {
            case 1:
            case 2:
            case 4:
            case 8: png_ptr->channels = 1; break;
            default: png_error(png_ptr, "Invalid bit depth for paletted image");
         }
         break;
      case PNG_COLOR_TYPE_GRAY_ALPHA:
         if (bit_depth != 8 && bit_depth != 16)
            png_error(png_ptr, "Invalid bit depth for grayscale+alpha image");
         png_ptr->channels = 2;
         break;
      case PNG_COLOR_TYPE_RGB_ALPHA:
         if (bit_depth != 8 && bit_depth != 16)
            png_error(png_ptr, "Invalid bit depth for RGBA image");
         png_ptr->channels = 4;
         break;
      default:
         png_error(png_ptr, "Invalid image color type specified");
   }

   if (compression_type != PNG_COMPRESSION_TYPE_BASE)
   {
      png_warning(png_ptr, "Invalid compression type specified");
      compression_type = PNG_COMPRESSION_TYPE_BASE;
   }

   /* Write filter_method 64 (intrapixel differencing) only if
    * 1. Libpng was compiled with PNG_MNG_FEATURES_SUPPORTED and
    * 2. Libpng did not write a PNG signature (this filter_method is only
    *    used in PNG datastreams that are embedded in MNG datastreams) and
    * 3. The application called png_permit_mng_features with a mask that
    *    included PNG_FLAG_MNG_FILTER_64 and
    * 4. The filter_method is 64 and
    * 5. The color_type is RGB or RGBA
    */
   if (
#ifdef PNG_MNG_FEATURES_SUPPORTED
      !((png_ptr->mng_features_permitted & PNG_FLAG_MNG_FILTER_64) &&
      ((png_ptr->mode&PNG_HAVE_PNG_SIGNATURE) == 0) &&
      (color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_RGB_ALPHA) &&
      (filter_type == PNG_INTRAPIXEL_DIFFERENCING)) &&
#endif
      filter_type != PNG_FILTER_TYPE_BASE)
   {
      png_warning(png_ptr, "Invalid filter type specified");
      filter_type = PNG_FILTER_TYPE_BASE;
   }

#ifdef PNG_WRITE_INTERLACING_SUPPORTED
   if (interlace_type != PNG_INTERLACE_NONE &&
      interlace_type != PNG_INTERLACE_ADAM7)
   {
      png_warning(png_ptr, "Invalid interlace type specified");
      interlace_type = PNG_INTERLACE_ADAM7;
   }
#else
   interlace_type=PNG_INTERLACE_NONE;
#endif

   /* Save the relevent information */
   png_ptr->bit_depth = (png_byte)bit_depth;
   png_ptr->color_type = (png_byte)color_type;
   png_ptr->interlaced = (png_byte)interlace_type;
#ifdef PNG_MNG_FEATURES_SUPPORTED
   png_ptr->filter_type = (png_byte)filter_type;
#endif
   png_ptr->compression_type = (png_byte)compression_type;
   png_ptr->width = width;
   png_ptr->height = height;

   png_ptr->pixel_depth = (png_byte)(bit_depth * png_ptr->channels);
   png_ptr->rowbytes = PNG_ROWBYTES(png_ptr->pixel_depth, width);
   /* Set the usr info, so any transformations can modify it */
   png_ptr->usr_width = png_ptr->width;
   png_ptr->usr_bit_depth = png_ptr->bit_depth;
   png_ptr->usr_channels = png_ptr->channels;

   /* Pack the header information into the buffer */
   png_save_uint_32(buf, width);
   png_save_uint_32(buf + 4, height);
   buf[8] = (png_byte)bit_depth;
   buf[9] = (png_byte)color_type;
   buf[10] = (png_byte)compression_type;
   buf[11] = (png_byte)filter_type;
   buf[12] = (png_byte)interlace_type;

   /* Write the chunk */
   png_write_chunk(png_ptr, (png_bytep)png_IHDR, buf, (png_size_t)13);

   /* Initialize zlib with PNG info */
   png_ptr->zstream.zalloc = png_zalloc;
   png_ptr->zstream.zfree = png_zfree;
   png_ptr->zstream.opaque = (voidpf)png_ptr;
   if (!(png_ptr->do_filter))
   {
      if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE ||
         png_ptr->bit_depth < 8)
         png_ptr->do_filter = PNG_FILTER_NONE;
      else
         png_ptr->do_filter = PNG_ALL_FILTERS;
   }
   if (!(png_ptr->flags & PNG_FLAG_ZLIB_CUSTOM_STRATEGY))
   {
      if (png_ptr->do_filter != PNG_FILTER_NONE)
         png_ptr->zlib_strategy = Z_FILTERED;
      else
         png_ptr->zlib_strategy = Z_DEFAULT_STRATEGY;
   }
   if (!(png_ptr->flags & PNG_FLAG_ZLIB_CUSTOM_LEVEL))
      png_ptr->zlib_level = Z_DEFAULT_COMPRESSION;
   if (!(png_ptr->flags & PNG_FLAG_ZLIB_CUSTOM_MEM_LEVEL))
      png_ptr->zlib_mem_level = 8;
   if (!(png_ptr->flags & PNG_FLAG_ZLIB_CUSTOM_WINDOW_BITS))
      png_ptr->zlib_window_bits = 15;
   if (!(png_ptr->flags & PNG_FLAG_ZLIB_CUSTOM_METHOD))
      png_ptr->zlib_method = 8;
   ret = deflateInit2(&png_ptr->zstream, png_ptr->zlib_level,
         png_ptr->zlib_method, png_ptr->zlib_window_bits,
         png_ptr->zlib_mem_level, png_ptr->zlib_strategy);
   if (ret != Z_OK)
   {
      if (ret == Z_VERSION_ERROR) png_error(png_ptr,
          "zlib failed to initialize compressor -- version error");
      if (ret == Z_STREAM_ERROR) png_error(png_ptr,
           "zlib failed to initialize compressor -- stream error");
      if (ret == Z_MEM_ERROR) png_error(png_ptr,
           "zlib failed to initialize compressor -- mem error");
      png_error(png_ptr, "zlib failed to initialize compressor");
   }
   png_ptr->zstream.next_out = png_ptr->zbuf;
   png_ptr->zstream.avail_out = (uInt)png_ptr->zbuf_size;
   /* libpng is not interested in zstream.data_type */
   /* Set it to a predefined value, to avoid its evaluation inside zlib */
   png_ptr->zstream.data_type = Z_BINARY;

   png_ptr->mode = PNG_HAVE_IHDR;
}
