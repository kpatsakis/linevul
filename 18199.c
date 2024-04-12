METHODDEF(JDIMENSION)
get_text_rgb_cmyk_row(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
/* This version is for reading text-format PPM files with any maxval and
   converting to CMYK */
{
  ppm_source_ptr source = (ppm_source_ptr)sinfo;
  FILE *infile = source->pub.input_file;
  register JSAMPROW ptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;
  unsigned int maxval = source->maxval;

  ptr = source->pub.buffer[0];
  if (maxval == MAXJSAMPLE) {
    for (col = cinfo->image_width; col > 0; col--) {
      JSAMPLE r = read_pbm_integer(cinfo, infile, maxval);
      JSAMPLE g = read_pbm_integer(cinfo, infile, maxval);
      JSAMPLE b = read_pbm_integer(cinfo, infile, maxval);
      rgb_to_cmyk(r, g, b, ptr, ptr + 1, ptr + 2, ptr + 3);
      ptr += 4;
    }
  } else {
    for (col = cinfo->image_width; col > 0; col--) {
      JSAMPLE r = rescale[read_pbm_integer(cinfo, infile, maxval)];
      JSAMPLE g = rescale[read_pbm_integer(cinfo, infile, maxval)];
      JSAMPLE b = rescale[read_pbm_integer(cinfo, infile, maxval)];
      rgb_to_cmyk(r, g, b, ptr, ptr + 1, ptr + 2, ptr + 3);
      ptr += 4;
    }
  }
  return 1;
}