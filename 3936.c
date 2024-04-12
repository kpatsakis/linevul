pkinit_fini_req_crypto(pkinit_req_crypto_context req_cryptoctx)
{
    if (req_cryptoctx == NULL)
        return;

    pkiDebug("%s: freeing ctx at %p\n", __FUNCTION__, req_cryptoctx);
    if (req_cryptoctx->dh != NULL)
        DH_free(req_cryptoctx->dh);
    if (req_cryptoctx->received_cert != NULL)
        X509_free(req_cryptoctx->received_cert);

    free(req_cryptoctx);
}
