static int rsa_priv_decode(EVP_PKEY *pkey, PKCS8_PRIV_KEY_INFO *p8)
{
    const unsigned char *p;
    int pklen;
    if (!PKCS8_pkey_get0(NULL, &p, &pklen, NULL, p8))
        return 0;
    return old_rsa_priv_decode(pkey, &p, pklen);
}
