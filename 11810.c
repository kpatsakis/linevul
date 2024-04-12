ghash_internal (gcry_cipher_hd_t c, byte *result, const byte *buf,
                size_t nblocks)
{
  const unsigned int blocksize = GCRY_GCM_BLOCK_LEN;
  unsigned int burn = 0;

  prefetch_tables (c);

  while (nblocks)
    {
      burn = GHASH (c, result, buf);
      buf += blocksize;
      nblocks--;
    }

  return burn + (burn ? 5*sizeof(void*) : 0);
}
