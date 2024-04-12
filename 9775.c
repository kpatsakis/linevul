int ossl_statem_in_error(const SSL *s)
{
    if (s->statem.state == MSG_FLOW_ERROR)
        return 1;

    return 0;
}
