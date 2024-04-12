int wc_X963_KDF(enum wc_HashType type, const byte* secret, word32 secretSz,
                const byte* sinfo, word32 sinfoSz, byte* out, word32 outSz)
{
    int ret, i;
    int digestSz, copySz;
    int remaining = outSz;
    byte* outIdx;
    byte  counter[4];
    byte  tmp[WC_MAX_DIGEST_SIZE];

#ifdef WOLFSSL_SMALL_STACK
    wc_HashAlg* hash;
#else
    wc_HashAlg hash[1];
#endif

    if (secret == NULL || secretSz == 0 || out == NULL)
        return BAD_FUNC_ARG;

    /* X9.63 allowed algos only */
    if (type != WC_HASH_TYPE_SHA    && type != WC_HASH_TYPE_SHA224 &&
        type != WC_HASH_TYPE_SHA256 && type != WC_HASH_TYPE_SHA384 &&
        type != WC_HASH_TYPE_SHA512)
        return BAD_FUNC_ARG;

    digestSz = wc_HashGetDigestSize(type);
    if (digestSz < 0)
        return digestSz;

#ifdef WOLFSSL_SMALL_STACK
    hash = (wc_HashAlg*)XMALLOC(sizeof(wc_HashAlg), NULL,
                                DYNAMIC_TYPE_HASHES);
    if (hash == NULL)
        return MEMORY_E;
#endif

    ret = wc_HashInit(hash, type);
    if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
        XFREE(hash, NULL, DYNAMIC_TYPE_HASHES);
#endif
        return ret;
    }

    outIdx = out;
    XMEMSET(counter, 0, sizeof(counter));

    for (i = 1; remaining > 0; i++) {

        IncrementX963KdfCounter(counter);

        ret = wc_HashUpdate(hash, type, secret, secretSz);
        if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
            XFREE(hash, NULL, DYNAMIC_TYPE_HASHES);
#endif
            return ret;
        }

        ret = wc_HashUpdate(hash, type, counter, sizeof(counter));
        if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
            XFREE(hash, NULL, DYNAMIC_TYPE_HASHES);
#endif
            return ret;
        }

        if (sinfo) {
            ret = wc_HashUpdate(hash, type, sinfo, sinfoSz);
            if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
                XFREE(hash, NULL, DYNAMIC_TYPE_HASHES);
#endif
                return ret;
            }
        }

        ret = wc_HashFinal(hash, type, tmp);
        if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
            XFREE(hash, NULL, DYNAMIC_TYPE_HASHES);
#endif
            return ret;
        }

        copySz = min(remaining, digestSz);
        XMEMCPY(outIdx, tmp, copySz);

        remaining -= copySz;
        outIdx += copySz;
    }

#ifdef WOLFSSL_SMALL_STACK
     XFREE(hash, NULL, DYNAMIC_TYPE_HASHES);
#endif

    return 0;
}
