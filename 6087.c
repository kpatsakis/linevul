png_write_zTXt(png_structp png_ptr, png_charp key, png_charp text,
   png_size_t text_len, int compression)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_zTXt;
#endif
   png_size_t key_len;
   char buf[1];
   png_charp new_key;
   compression_state comp;

   png_debug(1, "in png_write_zTXt");

   comp.num_output_ptr = 0;
   comp.max_output_ptr = 0;
   comp.output_ptr = NULL;
   comp.input = NULL;
   comp.input_len = 0;

   if ((key_len = png_check_keyword(png_ptr, key, &new_key))==0)
   {
      png_free(png_ptr, new_key);
      return;
   }

   if (text == NULL || *text == '\0' || compression==PNG_TEXT_COMPRESSION_NONE)
   {
      png_write_tEXt(png_ptr, new_key, text, (png_size_t)0);
      png_free(png_ptr, new_key);
      return;
   }

   text_len = png_strlen(text);

   /* Compute the compressed data; do it now for the length */
   text_len = png_text_compress(png_ptr, text, text_len, compression,
       &comp);

   /* Write start of chunk */
   png_write_chunk_start(png_ptr, (png_bytep)png_zTXt,
     (png_uint_32)(key_len+text_len + 2));
   /* Write key */
   png_write_chunk_data(png_ptr, (png_bytep)new_key,
     (png_size_t)(key_len + 1));
   png_free(png_ptr, new_key);

   buf[0] = (png_byte)compression;
   /* Write compression */
   png_write_chunk_data(png_ptr, (png_bytep)buf, (png_size_t)1);
   /* Write the compressed data */
   png_write_compressed_data_out(png_ptr, &comp);

   /* Close the chunk */
   png_write_chunk_end(png_ptr);
}
