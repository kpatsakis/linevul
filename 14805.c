DEFINE_RUN_ONCE_STATIC_ALT(ossl_init_no_config, ossl_init_config)
{
#ifdef OPENSSL_INIT_DEBUG
    fprintf(stderr,
            "OPENSSL_INIT: ossl_init_config: openssl_no_config_int()\n");
#endif
    openssl_no_config_int();
    config_inited = 1;
    return 1;
}
