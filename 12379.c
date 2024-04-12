size_t ZSTD_estimateCCtxSize_usingCParams(ZSTD_compressionParameters cParams)
{
    ZSTD_CCtx_params const params = ZSTD_makeCCtxParamsFromCParams(cParams);
    return ZSTD_estimateCCtxSize_usingCCtxParams(&params);
}
