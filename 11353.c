png_get_libpng_ver(png_structp png_ptr)
{
   /* Version of *.c files used when building libpng */
   PNG_UNUSED(png_ptr)  /* Silence compiler warning about unused png_ptr */
   return ((png_charp) PNG_LIBPNG_VER_STRING);
}
