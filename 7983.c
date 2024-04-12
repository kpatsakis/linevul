ecEncCtx* wc_ecc_ctx_new(int flags, WC_RNG* rng)
{
    return wc_ecc_ctx_new_ex(flags, rng, NULL);
}
