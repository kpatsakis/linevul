int dtls1_write_bytes(SSL *s, int type, const void *buf, int len)
{
    int i;

    OPENSSL_assert(len <= SSL3_RT_MAX_PLAIN_LENGTH);
    s->rwstate = SSL_NOTHING;
    i = do_dtls1_write(s, type, buf, len, 0);
    return i;
}
