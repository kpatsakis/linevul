setupM (gcry_cipher_hd_t c)
{
#if defined(GCM_USE_INTEL_PCLMUL) || defined(GCM_USE_ARM_PMULL)
  unsigned int features = _gcry_get_hw_features ();
#endif

  if (0)
    ;
#ifdef GCM_USE_INTEL_PCLMUL
  else if (features & HWF_INTEL_PCLMUL)
    {
      c->u_mode.gcm.ghash_fn = _gcry_ghash_intel_pclmul;
      _gcry_ghash_setup_intel_pclmul (c);
    }
#endif
#ifdef GCM_USE_ARM_PMULL
  else if (features & HWF_ARM_PMULL)
    {
      c->u_mode.gcm.ghash_fn = ghash_armv8_ce_pmull;
      ghash_setup_armv8_ce_pmull (c);
    }
#endif
#ifdef GCM_USE_ARM_NEON
  else if (features & HWF_ARM_NEON)
    {
      c->u_mode.gcm.ghash_fn = ghash_armv7_neon;
      ghash_setup_armv7_neon (c);
    }
#endif
  else
    {
      c->u_mode.gcm.ghash_fn = ghash_internal;
      fillM (c);
    }
}
