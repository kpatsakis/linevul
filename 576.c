size_t ZSTD_initCStream_usingCDict(ZSTD_CStream* zcs, const ZSTD_CDict* cdict)
{
    ZSTD_frameParameters const fParams = { 0 /* contentSizeFlag */, 0 /* checksum */, 0 /* hideDictID */ };
    DEBUGLOG(4, "ZSTD_initCStream_usingCDict");
    return ZSTD_initCStream_usingCDict_advanced(zcs, cdict, fParams, ZSTD_CONTENTSIZE_UNKNOWN);  /* note : will check that cdict != NULL */
}
