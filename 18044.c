DEFINE_RUN_ONCE_STATIC(ossl_init_engine_openssl)
{
# ifdef OPENSSL_INIT_DEBUG
    fprintf(stderr, "OPENSSL_INIT: ossl_init_engine_openssl: "
                    "engine_load_openssl_int()\n");
# endif
    engine_load_openssl_int();
    return 1;
}
