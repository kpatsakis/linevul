static void ecc_ctx_init(ecEncCtx* ctx, int flags)
{
    if (ctx) {
        XMEMSET(ctx, 0, sizeof(ecEncCtx));

        ctx->encAlgo  = ecAES_128_CBC;
        ctx->kdfAlgo  = ecHKDF_SHA256;
        ctx->macAlgo  = ecHMAC_SHA256;
        ctx->protocol = (byte)flags;

        if (flags == REQ_RESP_CLIENT)
            ctx->cliSt = ecCLI_INIT;
        if (flags == REQ_RESP_SERVER)
            ctx->srvSt = ecSRV_INIT;
    }
}
