read_chunk(struct file *file)
 /* On entry file::data_pos must be set to the position of the first byte
    * of the chunk data *and* the input file must be at this position.  This
    * routine (via process_chunk) instantiates a chunk or IDAT control structure
    * based on file::length and file::type and also resets these fields and
    * file::data_pos for the chunk after this one.  For an IDAT chunk the whole
    * stream of IDATs will be read, until something other than an IDAT is
    * encountered, and the file fields will be set for the chunk after the end
    * of the stream of IDATs.
    *
    * For IEND the file::type field will be set to 0, and nothing beyond the end
    * of the IEND chunk will have been read.
    */
{
   png_uint_32 length = file->length;
   png_uint_32 type = file->type;

 /* After IEND file::type is set to 0, if libpng attempts to read
    * more data at this point this is a bug in libpng.
    */
 if (type == 0)
      stop(file, UNEXPECTED_ERROR_CODE, "read beyond IEND");

 if (file->global->verbose > 2)
 {
      fputs("   ", stderr);
      type_name(type, stderr);
      fprintf(stderr, " %lu\n", (unsigned long)length);
 }

 /* Start the read_crc calculation with the chunk type, then read to the end
    * of the chunk data (without processing it in any way) to check that it is
    * all there and calculate the CRC.
    */
   file->crc = crc_init_4(type);
 if (crc_read_many(file, length)) /* else it was truncated */
 {
      png_uint_32 file_crc; /* CRC read from file */
 unsigned int nread = read_4(file, &file_crc);

 if (nread == 4)
 {
 if (type != png_IEND) /* do not read beyond IEND */
 {
            png_uint_32 next_length;

            nread += read_4(file, &next_length);
 if (nread == 8 && next_length <= 0x7fffffff)
 {
               png_uint_32 next_type;

               nread += read_4(file, &next_type);

 if (nread == 12 && chunk_type_valid(next_type))
 {
 /* Adjust the read count back to the correct value for this
                   * chunk.
                   */
                  file->read_count -= 8;
                  process_chunk(file, file_crc, next_length, next_type);
 return;
 }
 }
 }

 else /* IEND */
 {
            process_chunk(file, file_crc, 0, 0);
 return;
 }
 }
 }

 /* Control gets to here if the the stream seems invalid or damaged in some
    * way.  Either there was a problem reading all the expected data (this
    * chunk's data, its CRC and the length and type of the next chunk) or the
    * next chunk length/type are invalid.  Notice that the cases that end up
    * here all correspond to cases that would otherwise terminate the read of
    * the PNG file.
    */
   sync_stream(file);
}
