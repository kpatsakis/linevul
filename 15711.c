ossl_cipher_is_authenticated(VALUE self)
{
    EVP_CIPHER_CTX *ctx;

    GetCipher(self, ctx);

    return (EVP_CIPHER_CTX_flags(ctx) & EVP_CIPH_FLAG_AEAD_CIPHER) ? Qtrue : Qfalse;
}
