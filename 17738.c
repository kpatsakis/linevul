void ossl_statem_set_in_init(SSL *s, int init)
{
    s->statem.in_init = init;
}
