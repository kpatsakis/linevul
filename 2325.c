static int ecc_check_pubkey_order(ecc_key* key, ecc_point* pubkey, mp_int* a,
        mp_int* prime, mp_int* order)
{
    ecc_point* inf = NULL;
    int        err;

    if (key == NULL)
        return BAD_FUNC_ARG;

    inf = wc_ecc_new_point_h(key->heap);
    if (inf == NULL)
        err = MEMORY_E;
    else {
#ifdef WOLFSSL_HAVE_SP_ECC
#ifndef WOLFSSL_SP_NO_256
        if (key->idx != ECC_CUSTOM_IDX &&
                                       ecc_sets[key->idx].id == ECC_SECP256R1) {
            err = sp_ecc_mulmod_256(order, pubkey, inf, 1, key->heap);
        }
        else
#endif
#endif
#ifndef WOLFSSL_SP_MATH
            err = wc_ecc_mulmod_ex(order, pubkey, inf, a, prime, 1, key->heap);
        if (err == MP_OKAY && !wc_ecc_point_is_at_infinity(inf))
            err = ECC_INF_E;
#else
            (void)a;
            (void)prime;

            err = WC_KEY_SIZE_E;
#endif
    }

    wc_ecc_del_point_h(inf, key->heap);

    return err;
}
