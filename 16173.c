size_t ZSTD_CCtx_setParametersUsingCCtxParams(
        ZSTD_CCtx* cctx, const ZSTD_CCtx_params* params)
{
    DEBUGLOG(4, "ZSTD_CCtx_setParametersUsingCCtxParams");
    if (cctx->streamStage != zcss_init) return ERROR(stage_wrong);
    if (cctx->cdict) return ERROR(stage_wrong);

    cctx->requestedParams = *params;
    return 0;
}
