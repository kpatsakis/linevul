static vpx_codec_err_t decoder_peek_si(const uint8_t *data,
 unsigned int data_sz,
 vpx_codec_stream_info_t *si) {
 return decoder_peek_si_internal(data, data_sz, si, NULL, NULL, NULL);
}
