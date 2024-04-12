int CRYPTO_THREAD_set_local(CRYPTO_THREAD_LOCAL *key, void *val)
{
    if (*key >= OPENSSL_CRYPTO_THREAD_LOCAL_KEY_MAX)
        return 0;

    thread_local_storage[*key] = val;

    return 1;
}
