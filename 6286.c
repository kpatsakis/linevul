_gcry_cipher_gcm_authenticate (gcry_cipher_hd_t c,
                               const byte * aadbuf, size_t aadbuflen)
{
  static const unsigned char zerobuf[MAX_BLOCKSIZE];

  if (c->spec->blocksize != GCRY_GCM_BLOCK_LEN)
    return GPG_ERR_CIPHER_ALGO;
  if (c->u_mode.gcm.datalen_over_limits)
    return GPG_ERR_INV_LENGTH;
  if (c->marks.tag
      || c->u_mode.gcm.ghash_aad_finalized
      || c->u_mode.gcm.ghash_data_finalized
      || !c->u_mode.gcm.ghash_fn)
    return GPG_ERR_INV_STATE;

  if (!c->marks.iv)
    _gcry_cipher_gcm_setiv (c, zerobuf, GCRY_GCM_BLOCK_LEN);

  gcm_bytecounter_add(c->u_mode.gcm.aadlen, aadbuflen);
  if (!gcm_check_aadlen_or_ivlen(c->u_mode.gcm.aadlen))
    {
      c->u_mode.gcm.datalen_over_limits = 1;
      return GPG_ERR_INV_LENGTH;
    }

  do_ghash_buf(c, c->u_mode.gcm.u_tag.tag, aadbuf, aadbuflen, 0);

  return 0;
}
