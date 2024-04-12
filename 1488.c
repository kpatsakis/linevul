static void finalize_chunk(struct Buffer *res, struct Buffer *buf, char *charset, size_t charsetlen)
{
  char end = charset[charsetlen];
  charset[charsetlen] = '\0';
  mutt_ch_convert_string(&buf->data, charset, Charset, MUTT_ICONV_HOOK_FROM);
  charset[charsetlen] = end;
  mutt_mb_filter_unprintable(&buf->data);
  mutt_buffer_addstr(res, buf->data);
  FREE(&buf->data);
  mutt_buffer_init(buf);
}
