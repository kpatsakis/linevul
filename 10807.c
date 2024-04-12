static int huff_reader_build_canonical(HuffReader *r, int *code_lengths,
                                       int alphabet_size)
{
    int len = 0, sym, code = 0, ret;
    int max_code_length = 0;
    uint16_t *codes;

    /* special-case 1 symbol since the vlc reader cannot handle it */
    for (sym = 0; sym < alphabet_size; sym++) {
        if (code_lengths[sym] > 0) {
            len++;
            code = sym;
            if (len > 1)
                break;
        }
    }
    if (len == 1) {
        r->nb_symbols = 1;
        r->simple_symbols[0] = code;
        r->simple = 1;
        return 0;
    }

    for (sym = 0; sym < alphabet_size; sym++)
        max_code_length = FFMAX(max_code_length, code_lengths[sym]);

    if (max_code_length == 0 || max_code_length > MAX_HUFFMAN_CODE_LENGTH)
        return AVERROR(EINVAL);

    codes = av_malloc_array(alphabet_size, sizeof(*codes));
    if (!codes)
        return AVERROR(ENOMEM);

    code = 0;
    r->nb_symbols = 0;
    for (len = 1; len <= max_code_length; len++) {
        for (sym = 0; sym < alphabet_size; sym++) {
            if (code_lengths[sym] != len)
                continue;
            codes[sym] = code++;
            r->nb_symbols++;
        }
        code <<= 1;
    }
    if (!r->nb_symbols) {
        av_free(codes);
        return AVERROR_INVALIDDATA;
    }

    ret = init_vlc(&r->vlc, 8, alphabet_size,
                   code_lengths, sizeof(*code_lengths), sizeof(*code_lengths),
                   codes, sizeof(*codes), sizeof(*codes), 0);
    if (ret < 0) {
        av_free(codes);
        return ret;
    }
    r->simple = 0;

    av_free(codes);
    return 0;
}
