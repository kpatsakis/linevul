void rand_drbg_cleanup_entropy(RAND_DRBG *drbg,
                               unsigned char *out, size_t outlen)
{
    if (drbg->seed_pool == NULL) {
        if (drbg->secure)
            OPENSSL_secure_clear_free(out, outlen);
        else
            OPENSSL_clear_free(out, outlen);
    }
}
