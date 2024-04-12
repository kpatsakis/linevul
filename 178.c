ossl_cipher_set_auth_tag(VALUE self, VALUE vtag)
{
    EVP_CIPHER_CTX *ctx;
    unsigned char *tag;
    int tag_len;

    StringValue(vtag);
    tag = (unsigned char *) RSTRING_PTR(vtag);
    tag_len = RSTRING_LENINT(vtag);

    GetCipher(self, ctx);
    if (!(EVP_CIPHER_CTX_flags(ctx) & EVP_CIPH_FLAG_AEAD_CIPHER))
	ossl_raise(eCipherError, "authentication tag not supported by this cipher");

    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, tag_len, tag))
	ossl_raise(eCipherError, "unable to set AEAD tag");

    return vtag;
}
