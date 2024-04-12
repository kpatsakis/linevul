static INLINE void wc_ecc_reset(ecc_key* key)
{
    /* make sure required key variables are reset */
    key->state = ECC_STATE_NONE;
}
