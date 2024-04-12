zlib_check(struct file *file, png_uint_32 offset)
 /* Check the stream of zlib compressed data in either idat (if given) or (if
    * not) chunk.  In fact it is zlib_run that handles the difference in reading
    * a single chunk and a list of IDAT chunks.
    *
    * In either case the input file must be positioned at the first byte of zlib
    * compressed data (the first header byte).
    *
    * The return value is true on success, including the case where the zlib
    * header may need to be rewritten, and false on an unrecoverable error.
    *
    * In the case of IDAT chunks 'offset' should be 0.
    */
{
 fpos_t start_pos;
 struct zlib zlib;

 /* Record the start of the LZ data to allow a re-read. */
   file_getpos(file, &start_pos);

 /* First test the existing (file) window bits: */
 if (zlib_init(&zlib, file->idat, file->chunk, 0/*window bits*/, offset))
 {
 int min_bits, max_bits, rc;

 /* The first run using the existing window bits. */
      rc = zlib_run(&zlib);

 switch (rc)
 {
 case ZLIB_TOO_FAR_BACK:
 /* too far back error */
            file->status_code |= TOO_FAR_BACK;
            min_bits = zlib.window_bits + 1;
            max_bits = 15;
 break;

 case ZLIB_STREAM_END:
 if (!zlib.global->optimize_zlib &&
               zlib.window_bits == zlib.file_bits && !zlib.cksum)
 {
 /* The trivial case where the stream is ok and optimization was
                * not requested.
                */
               zlib_end(&zlib);
 return 1;
 }

            max_bits = max_window_bits(zlib.uncompressed_bytes,
               zlib.uncompressed_digits);
 if (zlib.ok_bits < max_bits)
               max_bits = zlib.ok_bits;
            min_bits = 8;

 /* cksum is set if there is an error in the zlib header checksum
             * calculation in the original file (and this may be the only reason
             * a rewrite is required).  We can't rely on the file window bits in
             * this case, so do the optimization anyway.
             */
 if (zlib.cksum)
               chunk_message(zlib.chunk, "zlib checkum");
 break;


 case ZLIB_OK:
 /* Truncated stream; unrecoverable, gets converted to ZLIB_FATAL */
            zlib.z.msg = PNGZ_MSG_CAST("[truncated]");
            zlib_message(&zlib, 0/*expected*/);
 /* FALL THROUGH */

 default:
 /* Unrecoverable error; skip the chunk; a zlib_message has already
             * been output.
             */
            zlib_end(&zlib);
 return 0;
 }

 /* Optimize window bits or fix a too-far-back error.  min_bits and
       * max_bits have been set appropriately, ok_bits records the bit value
       * known to work.
       */
 while (min_bits < max_bits || max_bits < zlib.ok_bits/*if 16*/)
 {
 int test_bits = (min_bits + max_bits) >> 1;

 if (zlib_reset(&zlib, test_bits))
 {
            file_setpos(file, &start_pos);
            rc = zlib_run(&zlib);

 switch (rc)
 {
 case ZLIB_TOO_FAR_BACK:
                  min_bits = test_bits+1;
 if (min_bits > max_bits)
 {
 /* This happens when the stream really is damaged and it
                      * contains a distance code that addresses bytes before
                      * the start of the uncompressed data.
                      */
                     assert(test_bits == 15);

 /* Output the error that wasn't output before: */
 if (zlib.z.msg == NULL)
                        zlib.z.msg = PNGZ_MSG_CAST(
 "invalid distance too far back");
                     zlib_message(&zlib, 0/*stream error*/);
                     zlib_end(&zlib);
 return 0;
 }
 break;

 case ZLIB_STREAM_END: /* success */
                  max_bits = test_bits;
 break;

 default:
 /* A fatal error; this happens if a too-far-back error was
                   * hiding a more serious error, zlib_advance has already
                   * output a zlib_message.
                   */
                  zlib_end(&zlib);
 return 0;
 }
 }

 else /* inflateReset2 failed */
 {
            zlib_end(&zlib);
 return 0;
 }
 }

 /* The loop guarantees this */
      assert(zlib.ok_bits == max_bits);
      zlib_end(&zlib);
 return 1;
 }

 else /* zlib initialization failed - skip the chunk */
 {
      zlib_end(&zlib);
 return 0;
 }
}
