ossl_cipher_set_auth_data(VALUE self, VALUE data)
{
    EVP_CIPHER_CTX *ctx;
    unsigned char *in;
    long in_len, out_len;

    StringValue(data);

    in = (unsigned char *) RSTRING_PTR(data);
    in_len = RSTRING_LEN(data);

    GetCipher(self, ctx);

    if (!ossl_cipher_update_long(ctx, NULL, &out_len, in, in_len))
        ossl_raise(eCipherError, "couldn't set additional authenticated data");

    return data;
}
