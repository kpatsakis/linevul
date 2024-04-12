size_t ZSTD_CCtxParams_reset(ZSTD_CCtx_params* params)
{
    return ZSTD_CCtxParams_init(params, ZSTD_CLEVEL_DEFAULT);
}
