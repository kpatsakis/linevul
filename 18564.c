WORK_STATE ossl_statem_client_post_process_message(SSL *s, WORK_STATE wst)
{
    OSSL_STATEM *st = &s->statem;

    switch (st->hand_state) {
    case TLS_ST_CR_CERT_REQ:
        return tls_prepare_client_certificate(s, wst);

#ifndef OPENSSL_NO_SCTP
    case TLS_ST_CR_SRVR_DONE:
        /* We only get here if we are using SCTP and we are renegotiating */
        if (BIO_dgram_sctp_msg_waiting(SSL_get_rbio(s))) {
            s->s3->in_read_app_data = 2;
            s->rwstate = SSL_READING;
            BIO_clear_retry_flags(SSL_get_rbio(s));
            BIO_set_retry_read(SSL_get_rbio(s));
            ossl_statem_set_sctp_read_sock(s, 1);
            return WORK_MORE_A;
        }
        ossl_statem_set_sctp_read_sock(s, 0);
        return WORK_FINISHED_STOP;
#endif

    default:
        break;
    }

    /* Shouldn't happen */
    return WORK_ERROR;
}
