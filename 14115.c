pkinit_fini_pkinit_oids(pkinit_plg_crypto_context ctx)
{
    if (ctx == NULL)
        return;
    ASN1_OBJECT_free(ctx->id_pkinit_san);
    ASN1_OBJECT_free(ctx->id_pkinit_authData);
    ASN1_OBJECT_free(ctx->id_pkinit_DHKeyData);
    ASN1_OBJECT_free(ctx->id_pkinit_rkeyData);
    ASN1_OBJECT_free(ctx->id_pkinit_KPClientAuth);
    ASN1_OBJECT_free(ctx->id_pkinit_KPKdc);
    ASN1_OBJECT_free(ctx->id_ms_kp_sc_logon);
    ASN1_OBJECT_free(ctx->id_ms_san_upn);
    ASN1_OBJECT_free(ctx->id_kp_serverAuth);
}
