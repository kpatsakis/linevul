png_write_sCAL(png_structp png_ptr, int unit, double width, double height)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_sCAL;
#endif
   char buf[64];
   png_size_t total_len;

   png_debug(1, "in png_write_sCAL");

   buf[0] = (char)unit;
#ifdef _WIN32_WCE
/* sprintf() function is not supported on WindowsCE */
   {
      wchar_t wc_buf[32];
      size_t wc_len;
      swprintf(wc_buf, TEXT("%12.12e"), width);
      wc_len = wcslen(wc_buf);
      WideCharToMultiByte(CP_ACP, 0, wc_buf, -1, buf + 1, wc_len, NULL,
          NULL);
      total_len = wc_len + 2;
      swprintf(wc_buf, TEXT("%12.12e"), height);
      wc_len = wcslen(wc_buf);
      WideCharToMultiByte(CP_ACP, 0, wc_buf, -1, buf + total_len, wc_len,
         NULL, NULL);
      total_len += wc_len;
   }
#else
   png_snprintf(buf + 1, 63, "%12.12e", width);
   total_len = 1 + png_strlen(buf + 1) + 1;
   png_snprintf(buf + total_len, 64-total_len, "%12.12e", height);
   total_len += png_strlen(buf + total_len);
#endif

   png_debug1(3, "sCAL total length = %u", (unsigned int)total_len);
   png_write_chunk(png_ptr, (png_bytep)png_sCAL, (png_bytep)buf, total_len);
}
