size_t ZSTD_compressStream(ZSTD_CStream* zcs, ZSTD_outBuffer* output, ZSTD_inBuffer* input)
{
    /* check conditions */
    if (output->pos > output->size) return ERROR(GENERIC);
    if (input->pos  > input->size)  return ERROR(GENERIC);

    return ZSTD_compressStream_generic(zcs, output, input, ZSTD_e_continue);
}
