int wc_ecc_get_curve_id_from_params(int fieldSize,
        const byte* prime, word32 primeSz, const byte* Af, word32 AfSz,
        const byte* Bf, word32 BfSz, const byte* order, word32 orderSz,
        const byte* Gx, word32 GxSz, const byte* Gy, word32 GySz, int cofactor)
{
    int idx;
    int curveSz;

    if (prime == NULL || Af == NULL || Bf == NULL || order == NULL ||
        Gx == NULL || Gy == NULL)
        return BAD_FUNC_ARG;

    curveSz = (fieldSize + 1) / 8;    /* round up */

    for (idx = 0; ecc_sets[idx].size != 0; idx++) {
        if (curveSz == ecc_sets[idx].size) {
            if ((wc_ecc_cmp_param(ecc_sets[idx].prime, prime,
                            primeSz) == MP_EQ) &&
                (wc_ecc_cmp_param(ecc_sets[idx].Af, Af, AfSz) == MP_EQ) &&
                (wc_ecc_cmp_param(ecc_sets[idx].Bf, Bf, BfSz) == MP_EQ) &&
                (wc_ecc_cmp_param(ecc_sets[idx].order, order,
                                  orderSz) == MP_EQ) &&
                (wc_ecc_cmp_param(ecc_sets[idx].Gx, Gx, GxSz) == MP_EQ) &&
                (wc_ecc_cmp_param(ecc_sets[idx].Gy, Gy, GySz) == MP_EQ) &&
                (cofactor == ecc_sets[idx].cofactor)) {
                    break;
            }
        }
    }

    if (ecc_sets[idx].size == 0)
        return ECC_CURVE_INVALID;

    return ecc_sets[idx].id;
}
