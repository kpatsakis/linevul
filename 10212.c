static int tls1_alpn_handle_client_hello_late(SSL *s, int *ret, int *al)
{
    const unsigned char *selected = NULL;
    unsigned char selected_len = 0;

    if (s->ctx->alpn_select_cb != NULL && s->cert->alpn_proposed != NULL) {
        int r = s->ctx->alpn_select_cb(s, &selected, &selected_len,
                                       s->cert->alpn_proposed,
                                       s->cert->alpn_proposed_len,
                                       s->ctx->alpn_select_cb_arg);

        if (r == SSL_TLSEXT_ERR_OK) {
            OPENSSL_free(s->s3->alpn_selected);
            s->s3->alpn_selected = OPENSSL_malloc(selected_len);
            if (s->s3->alpn_selected == NULL) {
                *al = SSL_AD_INTERNAL_ERROR;
                *ret = SSL_TLSEXT_ERR_ALERT_FATAL;
                return 0;
            }
            memcpy(s->s3->alpn_selected, selected, selected_len);
            s->s3->alpn_selected_len = selected_len;
# ifndef OPENSSL_NO_NEXTPROTONEG
            /* ALPN takes precedence over NPN. */
            s->s3->next_proto_neg_seen = 0;
# endif
        }
    }

    return 1;
}
