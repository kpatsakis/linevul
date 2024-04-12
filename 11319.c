_gcry_aes_cfb_dec (void *context, unsigned char *iv,
                   void *outbuf_arg, const void *inbuf_arg,
                   size_t nblocks)
{
  RIJNDAEL_context *ctx = context;
  unsigned char *outbuf = outbuf_arg;
  const unsigned char *inbuf = inbuf_arg;
  unsigned int burn_depth = 0;

  if (0)
    ;
#ifdef USE_AESNI
  else if (ctx->use_aesni)
    {
      _gcry_aes_aesni_cfb_dec (ctx, iv, outbuf, inbuf, nblocks);
      return;
    }
#endif /*USE_AESNI*/
#ifdef USE_SSSE3
  else if (ctx->use_ssse3)
    {
      _gcry_aes_ssse3_cfb_dec (ctx, iv, outbuf, inbuf, nblocks);
      return;
    }
#endif /*USE_SSSE3*/
#ifdef USE_ARM_CE
  else if (ctx->use_arm_ce)
    {
      _gcry_aes_armv8_ce_cfb_dec (ctx, iv, outbuf, inbuf, nblocks);
      return;
    }
#endif /*USE_ARM_CE*/
  else
    {
      rijndael_cryptfn_t encrypt_fn = ctx->encrypt_fn;

      if (ctx->prefetch_enc_fn)
        ctx->prefetch_enc_fn();

      for ( ;nblocks; nblocks-- )
        {
          burn_depth = encrypt_fn (ctx, iv, iv);
          cipher_block_xor_n_copy(outbuf, iv, inbuf, BLOCKSIZE);
          outbuf += BLOCKSIZE;
          inbuf  += BLOCKSIZE;
        }
    }

  if (burn_depth)
    _gcry_burn_stack (burn_depth + 4 * sizeof(void *));
}
