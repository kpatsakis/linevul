EC_PRE_COMP *EC_ec_pre_comp_dup(EC_PRE_COMP *pre)
{
    int i;
    if (pre != NULL)
        CRYPTO_atomic_add(&pre->references, 1, &i, pre->lock);
    return pre;
}
