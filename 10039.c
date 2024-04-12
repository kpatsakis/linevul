prepare_decryption( RIJNDAEL_context *ctx )
{
  int r;

  if (0)
    ;
#ifdef USE_AESNI
  else if (ctx->use_aesni)
    {
      _gcry_aes_aesni_prepare_decryption (ctx);
    }
#endif /*USE_AESNI*/
#ifdef USE_SSSE3
  else if (ctx->use_ssse3)
    {
      _gcry_aes_ssse3_prepare_decryption (ctx);
    }
#endif /*USE_SSSE3*/
#ifdef USE_ARM_CE
  else if (ctx->use_arm_ce)
    {
      _gcry_aes_armv8_ce_prepare_decryption (ctx);
    }
#endif /*USE_SSSE3*/
#ifdef USE_PADLOCK
  else if (ctx->use_padlock)
    {
      /* Padlock does not need decryption subkeys. */
    }
#endif /*USE_PADLOCK*/
  else
    {
      const byte *sbox = ((const byte *)encT) + 1;

      prefetch_enc();
      prefetch_dec();

      ctx->keyschdec32[0][0] = ctx->keyschenc32[0][0];
      ctx->keyschdec32[0][1] = ctx->keyschenc32[0][1];
      ctx->keyschdec32[0][2] = ctx->keyschenc32[0][2];
      ctx->keyschdec32[0][3] = ctx->keyschenc32[0][3];

      for (r = 1; r < ctx->rounds; r++)
        {
          u32 *wi = ctx->keyschenc32[r];
          u32 *wo = ctx->keyschdec32[r];
          u32 wt;

          wt = wi[0];
          wo[0] = rol(decT[sbox[(byte)(wt >> 0) * 4]], 8 * 0)
                 ^ rol(decT[sbox[(byte)(wt >> 8) * 4]], 8 * 1)
                 ^ rol(decT[sbox[(byte)(wt >> 16) * 4]], 8 * 2)
                 ^ rol(decT[sbox[(byte)(wt >> 24) * 4]], 8 * 3);

          wt = wi[1];
          wo[1] = rol(decT[sbox[(byte)(wt >> 0) * 4]], 8 * 0)
                 ^ rol(decT[sbox[(byte)(wt >> 8) * 4]], 8 * 1)
                 ^ rol(decT[sbox[(byte)(wt >> 16) * 4]], 8 * 2)
                 ^ rol(decT[sbox[(byte)(wt >> 24) * 4]], 8 * 3);

          wt = wi[2];
          wo[2] = rol(decT[sbox[(byte)(wt >> 0) * 4]], 8 * 0)
                 ^ rol(decT[sbox[(byte)(wt >> 8) * 4]], 8 * 1)
                 ^ rol(decT[sbox[(byte)(wt >> 16) * 4]], 8 * 2)
                 ^ rol(decT[sbox[(byte)(wt >> 24) * 4]], 8 * 3);

          wt = wi[3];
          wo[3] = rol(decT[sbox[(byte)(wt >> 0) * 4]], 8 * 0)
                 ^ rol(decT[sbox[(byte)(wt >> 8) * 4]], 8 * 1)
                 ^ rol(decT[sbox[(byte)(wt >> 16) * 4]], 8 * 2)
                 ^ rol(decT[sbox[(byte)(wt >> 24) * 4]], 8 * 3);
        }

      ctx->keyschdec32[r][0] = ctx->keyschenc32[r][0];
      ctx->keyschdec32[r][1] = ctx->keyschenc32[r][1];
      ctx->keyschdec32[r][2] = ctx->keyschenc32[r][2];
      ctx->keyschdec32[r][3] = ctx->keyschenc32[r][3];
    }
}
