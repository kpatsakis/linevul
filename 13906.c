dup_dh_params(const DH *src)
{
    const BIGNUM *oldp, *oldq, *oldg;
    BIGNUM *p = NULL, *q = NULL, *g = NULL;
    DH *dh;

    DH_get0_pqg(src, &oldp, &oldq, &oldg);
    p = BN_dup(oldp);
    q = BN_dup(oldq);
    g = BN_dup(oldg);
    dh = DH_new();
    if (p == NULL || q == NULL || g == NULL || dh == NULL) {
        BN_free(p);
        BN_free(q);
        BN_free(g);
        DH_free(dh);
        return NULL;
    }
    DH_set0_pqg(dh, p, q, g);
    return dh;
}
