static int aesni_ccm_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                              const unsigned char *iv, int enc)
{
    EVP_AES_CCM_CTX *cctx = EVP_C_DATA(EVP_AES_CCM_CTX,ctx);
    if (!iv && !key)
        return 1;
    if (key) {
        aesni_set_encrypt_key(key, EVP_CIPHER_CTX_key_length(ctx) * 8,
                              &cctx->ks.ks);
        CRYPTO_ccm128_init(&cctx->ccm, cctx->M, cctx->L,
                           &cctx->ks, (block128_f) aesni_encrypt);
        cctx->str = enc ? (ccm128_f) aesni_ccm64_encrypt_blocks :
            (ccm128_f) aesni_ccm64_decrypt_blocks;
        cctx->key_set = 1;
    }
    if (iv) {
        memcpy(EVP_CIPHER_CTX_iv_noconst(ctx), iv, 15 - cctx->L);
        cctx->iv_set = 1;
    }
    return 1;
}
