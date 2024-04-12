png_read_end(png_structp png_ptr, png_infop info_ptr)
{
   png_debug(1, "in png_read_end");
 
   if (png_ptr == NULL)
      return;
   png_crc_finish(png_ptr, 0); /* Finish off CRC from last IDAT chunk */

   do
   {
#ifdef PNG_USE_LOCAL_ARRAYS
      PNG_CONST PNG_IHDR;
      PNG_CONST PNG_IDAT;
      PNG_CONST PNG_IEND;
      PNG_CONST PNG_PLTE;
#ifdef PNG_READ_bKGD_SUPPORTED
      PNG_CONST PNG_bKGD;
#endif
#ifdef PNG_READ_cHRM_SUPPORTED
      PNG_CONST PNG_cHRM;
#endif
#ifdef PNG_READ_gAMA_SUPPORTED
      PNG_CONST PNG_gAMA;
#endif
#ifdef PNG_READ_hIST_SUPPORTED
      PNG_CONST PNG_hIST;
#endif
#ifdef PNG_READ_iCCP_SUPPORTED
      PNG_CONST PNG_iCCP;
#endif
#ifdef PNG_READ_iTXt_SUPPORTED
      PNG_CONST PNG_iTXt;
#endif
#ifdef PNG_READ_oFFs_SUPPORTED
      PNG_CONST PNG_oFFs;
#endif
#ifdef PNG_READ_pCAL_SUPPORTED
      PNG_CONST PNG_pCAL;
#endif
#ifdef PNG_READ_pHYs_SUPPORTED
      PNG_CONST PNG_pHYs;
#endif
#ifdef PNG_READ_sBIT_SUPPORTED
      PNG_CONST PNG_sBIT;
#endif
#ifdef PNG_READ_sCAL_SUPPORTED
      PNG_CONST PNG_sCAL;
#endif
#ifdef PNG_READ_sPLT_SUPPORTED
      PNG_CONST PNG_sPLT;
#endif
#ifdef PNG_READ_sRGB_SUPPORTED
      PNG_CONST PNG_sRGB;
#endif
#ifdef PNG_READ_tEXt_SUPPORTED
      PNG_CONST PNG_tEXt;
#endif
#ifdef PNG_READ_tIME_SUPPORTED
      PNG_CONST PNG_tIME;
#endif
#ifdef PNG_READ_tRNS_SUPPORTED
      PNG_CONST PNG_tRNS;
#endif
#ifdef PNG_READ_zTXt_SUPPORTED
      PNG_CONST PNG_zTXt;
#endif
#endif /* PNG_USE_LOCAL_ARRAYS */
      png_uint_32 length = png_read_chunk_header(png_ptr);
      PNG_CONST png_bytep chunk_name = png_ptr->chunk_name;

      if (!png_memcmp(chunk_name, png_IHDR, 4))
         png_handle_IHDR(png_ptr, info_ptr, length);
      else if (!png_memcmp(chunk_name, png_IEND, 4))
         png_handle_IEND(png_ptr, info_ptr, length);
#ifdef PNG_HANDLE_AS_UNKNOWN_SUPPORTED
      else if (png_handle_as_unknown(png_ptr, chunk_name))
      {
         if (!png_memcmp(chunk_name, png_IDAT, 4))
         {
            if ((length > 0) || (png_ptr->mode & PNG_HAVE_CHUNK_AFTER_IDAT))
               png_error(png_ptr, "Too many IDAT's found");
         }
         png_handle_unknown(png_ptr, info_ptr, length);
         if (!png_memcmp(chunk_name, png_PLTE, 4))
            png_ptr->mode |= PNG_HAVE_PLTE;
      }
#endif
      else if (!png_memcmp(chunk_name, png_IDAT, 4))
      {
         /* Zero length IDATs are legal after the last IDAT has been
          * read, but not after other chunks have been read.
          */
         if ((length > 0) || (png_ptr->mode & PNG_HAVE_CHUNK_AFTER_IDAT))
            png_error(png_ptr, "Too many IDAT's found");
         png_crc_finish(png_ptr, length);
      }
      else if (!png_memcmp(chunk_name, png_PLTE, 4))
         png_handle_PLTE(png_ptr, info_ptr, length);
#ifdef PNG_READ_bKGD_SUPPORTED
      else if (!png_memcmp(chunk_name, png_bKGD, 4))
         png_handle_bKGD(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_cHRM_SUPPORTED
      else if (!png_memcmp(chunk_name, png_cHRM, 4))
         png_handle_cHRM(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_gAMA_SUPPORTED
      else if (!png_memcmp(chunk_name, png_gAMA, 4))
         png_handle_gAMA(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_hIST_SUPPORTED
      else if (!png_memcmp(chunk_name, png_hIST, 4))
         png_handle_hIST(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_oFFs_SUPPORTED
      else if (!png_memcmp(chunk_name, png_oFFs, 4))
         png_handle_oFFs(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_pCAL_SUPPORTED
      else if (!png_memcmp(chunk_name, png_pCAL, 4))
         png_handle_pCAL(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_sCAL_SUPPORTED
      else if (!png_memcmp(chunk_name, png_sCAL, 4))
         png_handle_sCAL(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_pHYs_SUPPORTED
      else if (!png_memcmp(chunk_name, png_pHYs, 4))
         png_handle_pHYs(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_sBIT_SUPPORTED
      else if (!png_memcmp(chunk_name, png_sBIT, 4))
         png_handle_sBIT(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_sRGB_SUPPORTED
      else if (!png_memcmp(chunk_name, png_sRGB, 4))
         png_handle_sRGB(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_iCCP_SUPPORTED
      else if (!png_memcmp(chunk_name, png_iCCP, 4))
         png_handle_iCCP(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_sPLT_SUPPORTED
      else if (!png_memcmp(chunk_name, png_sPLT, 4))
         png_handle_sPLT(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_tEXt_SUPPORTED
      else if (!png_memcmp(chunk_name, png_tEXt, 4))
         png_handle_tEXt(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_tIME_SUPPORTED
      else if (!png_memcmp(chunk_name, png_tIME, 4))
         png_handle_tIME(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_tRNS_SUPPORTED
      else if (!png_memcmp(chunk_name, png_tRNS, 4))
         png_handle_tRNS(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_zTXt_SUPPORTED
      else if (!png_memcmp(chunk_name, png_zTXt, 4))
         png_handle_zTXt(png_ptr, info_ptr, length);
#endif
#ifdef PNG_READ_iTXt_SUPPORTED
      else if (!png_memcmp(chunk_name, png_iTXt, 4))
         png_handle_iTXt(png_ptr, info_ptr, length);
#endif
      else
         png_handle_unknown(png_ptr, info_ptr, length);
   } while (!(png_ptr->mode & PNG_HAVE_IEND));
}
