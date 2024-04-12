static int wc_ecc_curve_load(const ecc_set_type* dp, ecc_curve_spec** pCurve,
    byte load_mask)
{
    int ret = 0, x;
    ecc_curve_spec* curve;
    byte load_items = 0; /* mask of items to load */

    if (dp == NULL || pCurve == NULL)
        return BAD_FUNC_ARG;

#ifdef ECC_CACHE_CURVE
    x = wc_ecc_get_curve_idx(dp->id);
    if (x == ECC_CURVE_INVALID)
        return ECC_BAD_ARG_E;

#if !defined(SINGLE_THREADED)
    ret = wc_LockMutex(&ecc_curve_cache_mutex);
    if (ret != 0) {
        return ret;
    }
#endif

    /* make sure cache has been allocated */
    if (ecc_curve_spec_cache[x] == NULL) {
        ecc_curve_spec_cache[x] = (ecc_curve_spec*)XMALLOC(
            sizeof(ecc_curve_spec), NULL, DYNAMIC_TYPE_ECC);
        if (ecc_curve_spec_cache[x] == NULL) {
        #if defined(ECC_CACHE_CURVE) && !defined(SINGLE_THREADED)
            wc_UnLockMutex(&ecc_curve_cache_mutex);
        #endif
            return MEMORY_E;
        }
        XMEMSET(ecc_curve_spec_cache[x], 0, sizeof(ecc_curve_spec));
    }

    /* set curve pointer to cache */
    *pCurve = ecc_curve_spec_cache[x];

#endif /* ECC_CACHE_CURVE */
    curve = *pCurve;

    /* make sure the curve is initialized */
    if (curve->dp != dp) {
        curve->load_mask = 0;

    #ifdef ECC_CACHE_CURVE
        curve->prime = &curve->prime_lcl;
        curve->Af = &curve->Af_lcl;
        #ifdef USE_ECC_B_PARAM
            curve->Bf = &curve->Bf_lcl;
        #endif
        curve->order = &curve->order_lcl;
        curve->Gx = &curve->Gx_lcl;
        curve->Gy = &curve->Gy_lcl;
    #endif
    }
    curve->dp = dp; /* set dp info */

    /* determine items to load */
    load_items = (~curve->load_mask & load_mask);
    curve->load_mask |= load_items;

    /* load items */
    x = 0;
    if (load_items & ECC_CURVE_FIELD_PRIME)
        x += wc_ecc_curve_load_item(dp->prime, &curve->prime, curve,
            ECC_CURVE_FIELD_PRIME);
    if (load_items & ECC_CURVE_FIELD_AF)
        x += wc_ecc_curve_load_item(dp->Af, &curve->Af, curve,
            ECC_CURVE_FIELD_AF);
#ifdef USE_ECC_B_PARAM
    if (load_items & ECC_CURVE_FIELD_BF)
        x += wc_ecc_curve_load_item(dp->Bf, &curve->Bf, curve,
            ECC_CURVE_FIELD_BF);
#endif
    if (load_items & ECC_CURVE_FIELD_ORDER)
        x += wc_ecc_curve_load_item(dp->order, &curve->order, curve,
            ECC_CURVE_FIELD_ORDER);
    if (load_items & ECC_CURVE_FIELD_GX)
        x += wc_ecc_curve_load_item(dp->Gx, &curve->Gx, curve,
            ECC_CURVE_FIELD_GX);
    if (load_items & ECC_CURVE_FIELD_GY)
        x += wc_ecc_curve_load_item(dp->Gy, &curve->Gy, curve,
            ECC_CURVE_FIELD_GY);

    /* check for error */
    if (x != 0) {
        wc_ecc_curve_free(curve);
        ret = MP_READ_E;
    }

#if defined(ECC_CACHE_CURVE) && !defined(SINGLE_THREADED)
    wc_UnLockMutex(&ecc_curve_cache_mutex);
#endif

    return ret;
}
