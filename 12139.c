pngquant_error rwpng_write_image8(FILE *outfile, const png8_image *mainprog_ptr)
{
    png_structp png_ptr;
    png_infop info_ptr;

    if (mainprog_ptr->num_palette > 256) return INVALID_ARGUMENT;

    pngquant_error retval = rwpng_write_image_init((rwpng_png_image*)mainprog_ptr, &png_ptr, &info_ptr, mainprog_ptr->fast_compression);
    if (retval) return retval;

    struct rwpng_write_state write_state;
    write_state = (struct rwpng_write_state){
        .outfile = outfile,
        .maximum_file_size = mainprog_ptr->maximum_file_size,
        .retval = SUCCESS,
    };
    png_set_write_fn(png_ptr, &write_state, user_write_data, user_flush_data);

    png_set_filter(png_ptr, PNG_FILTER_TYPE_BASE, PNG_FILTER_VALUE_NONE);

    rwpng_set_gamma(info_ptr, png_ptr, mainprog_ptr->gamma, mainprog_ptr->output_color);

    /* set the image parameters appropriately */
    int sample_depth;
#if PNG_LIBPNG_VER > 10400 /* old libpng corrupts files with low depth */
    if (mainprog_ptr->num_palette <= 2)
        sample_depth = 1;
    else if (mainprog_ptr->num_palette <= 4)
        sample_depth = 2;
    else if (mainprog_ptr->num_palette <= 16)
        sample_depth = 4;
    else
#endif
        sample_depth = 8;

    struct rwpng_chunk *chunk = mainprog_ptr->chunks;
    int chunk_num=0;
    while(chunk) {
        png_unknown_chunk pngchunk = {
            .size = chunk->size,
            .data = chunk->data,
            .location = chunk->location,
        };
        memcpy(pngchunk.name, chunk->name, 5);
        png_set_unknown_chunks(png_ptr, info_ptr, &pngchunk, 1);

        #if defined(PNG_HAVE_IHDR) && PNG_LIBPNG_VER < 10600
        png_set_unknown_chunk_location(png_ptr, info_ptr, chunk_num, pngchunk.location ? pngchunk.location : PNG_HAVE_IHDR);
        #endif

        chunk = chunk->next;
        chunk_num++;
    }

    png_set_IHDR(png_ptr, info_ptr, mainprog_ptr->width, mainprog_ptr->height,
      sample_depth, PNG_COLOR_TYPE_PALETTE,
      0, PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_BASE);

    png_color palette[256];
    png_byte trans[256];
    unsigned int num_trans = 0;
    for(unsigned int i = 0; i < mainprog_ptr->num_palette; i++) {
        palette[i] = (png_color){
            .red   = mainprog_ptr->palette[i].r,
            .green = mainprog_ptr->palette[i].g,
            .blue  = mainprog_ptr->palette[i].b,
        };
        trans[i] = mainprog_ptr->palette[i].a;
        if (mainprog_ptr->palette[i].a < 255) {
            num_trans = i+1;
        }
    }

    png_set_PLTE(png_ptr, info_ptr, palette, mainprog_ptr->num_palette);

    if (num_trans > 0) {
        png_set_tRNS(png_ptr, info_ptr, trans, num_trans, NULL);
    }

    rwpng_write_end(&info_ptr, &png_ptr, mainprog_ptr->row_pointers);

    if (SUCCESS == write_state.retval && write_state.maximum_file_size && write_state.bytes_written > write_state.maximum_file_size) {
        return TOO_LARGE_FILE;
    }

    return write_state.retval;
}
