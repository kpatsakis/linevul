ZSTD_CCtx* ZSTD_createCCtx_advanced(ZSTD_customMem customMem)
{
    ZSTD_STATIC_ASSERT(zcss_init==0);
    ZSTD_STATIC_ASSERT(ZSTD_CONTENTSIZE_UNKNOWN==(0ULL - 1));
    if (!customMem.customAlloc ^ !customMem.customFree) return NULL;
    {   ZSTD_CCtx* const cctx = (ZSTD_CCtx*)ZSTD_malloc(sizeof(ZSTD_CCtx), customMem);
        if (!cctx) return NULL;
        ZSTD_initCCtx(cctx, customMem);
        return cctx;
    }
}
