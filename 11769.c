get_key(krb5_context context, pkinit_identity_crypto_context id_cryptoctx,
        char *filename, const char *fsname, EVP_PKEY **retkey,
        const char *password)
{
    EVP_PKEY *pkey = NULL;
    BIO *tmp = NULL;
    struct get_key_cb_data cb_data;
    int code;
    krb5_error_code retval;

    if (filename == NULL || retkey == NULL)
        return EINVAL;

    tmp = BIO_new(BIO_s_file());
    if (tmp == NULL)
        return ENOMEM;

    code = BIO_read_filename(tmp, filename);
    if (code == 0) {
        retval = errno;
        goto cleanup;
    }
    cb_data.context = context;
    cb_data.id_cryptoctx = id_cryptoctx;
    cb_data.filename = filename;
    cb_data.fsname = fsname;
    cb_data.password = password;
    pkey = PEM_read_bio_PrivateKey(tmp, NULL, get_key_cb, &cb_data);
    if (pkey == NULL && !id_cryptoctx->defer_id_prompt) {
        retval = EIO;
        pkiDebug("failed to read private key from %s\n", filename);
        goto cleanup;
    }
    *retkey = pkey;
    retval = 0;
cleanup:
    if (tmp != NULL)
        BIO_free(tmp);
    return retval;
}
