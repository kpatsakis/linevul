static int wc_ecc_shared_secret_gen_async(ecc_key* private_key,
            ecc_point* point, byte* out, word32 *outlen,
            ecc_curve_spec* curve)
{
    int err;

#if defined(HAVE_CAVIUM_V) || defined(HAVE_INTEL_QA)
#ifdef HAVE_CAVIUM_V
    /* verify the curve is supported by hardware */
    if (NitroxEccIsCurveSupported(private_key))
#endif
    {
        word32 keySz = private_key->dp->size;

        /* sync public key x/y */
        err = wc_mp_to_bigint_sz(&private_key->k, &private_key->k.raw, keySz);
        if (err == MP_OKAY)
            err = wc_mp_to_bigint_sz(point->x, &point->x->raw, keySz);
        if (err == MP_OKAY)
            err = wc_mp_to_bigint_sz(point->y, &point->y->raw, keySz);
    #ifdef HAVE_CAVIUM_V
        /* allocate buffer for output */
        if (err == MP_OKAY)
            err = wc_ecc_alloc_mpint(private_key, &private_key->e);
        if (err == MP_OKAY)
            err = wc_bigint_alloc(&private_key->e->raw,
                NitroxEccGetSize(private_key)*2);
        if (err == MP_OKAY)
            err = NitroxEcdh(private_key,
                &private_key->k.raw, &point->x->raw, &point->y->raw,
                private_key->e->raw.buf, &private_key->e->raw.len,
                &curve->prime->raw);
    #else
        if (err == MP_OKAY)
            err = wc_ecc_curve_load(private_key->dp, &curve, ECC_CURVE_FIELD_BF);
        if (err == MP_OKAY)
            err = IntelQaEcdh(&private_key->asyncDev,
                &private_key->k.raw, &point->x->raw, &point->y->raw,
                out, outlen,
                &curve->Af->raw, &curve->Bf->raw, &curve->prime->raw,
                private_key->dp->cofactor);
    #endif
        return err;
    }
#elif defined(WOLFSSL_ASYNC_CRYPT_TEST)
    if (wc_AsyncTestInit(&private_key->asyncDev, ASYNC_TEST_ECC_SHARED_SEC)) {
        WC_ASYNC_TEST* testDev = &private_key->asyncDev.test;
        testDev->eccSharedSec.private_key = private_key;
        testDev->eccSharedSec.public_point = point;
        testDev->eccSharedSec.out = out;
        testDev->eccSharedSec.outLen = outlen;
        return WC_PENDING_E;
    }
#endif

    /* use sync in other cases */
    err = wc_ecc_shared_secret_gen_sync(private_key, point, out, outlen, curve);

    return err;
}
