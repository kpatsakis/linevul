rijndael_setkey (void *context, const byte *key, const unsigned keylen,
                 gcry_cipher_hd_t hd)
{
  RIJNDAEL_context *ctx = context;
  return do_setkey (ctx, key, keylen, hd);
}
