stringprep_ucs4_nfkc_normalize (const uint32_t * str, ssize_t len)
{
  char *p;
  uint32_t *result_wc;

  p = stringprep_ucs4_to_utf8 (str, len, 0, 0);
  result_wc = _g_utf8_normalize_wc (p, -1, G_NORMALIZE_NFKC);
  free (p);

  return result_wc;
}
