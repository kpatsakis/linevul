static int wc_ecc_alloc_async(ecc_key* key)
{
    int err = wc_ecc_alloc_mpint(key, &key->r);
    if (err == 0)
        err = wc_ecc_alloc_mpint(key, &key->s);
    return err;
}
