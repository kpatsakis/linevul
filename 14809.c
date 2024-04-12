static int tls_process_ske_srp(SSL *s, PACKET *pkt, EVP_PKEY **pkey, int *al)
{
#ifndef OPENSSL_NO_SRP
    PACKET prime, generator, salt, server_pub;

    if (!PACKET_get_length_prefixed_2(pkt, &prime)
        || !PACKET_get_length_prefixed_2(pkt, &generator)
        || !PACKET_get_length_prefixed_1(pkt, &salt)
        || !PACKET_get_length_prefixed_2(pkt, &server_pub)) {
        *al = SSL_AD_DECODE_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_SKE_SRP, SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    if ((s->srp_ctx.N =
         BN_bin2bn(PACKET_data(&prime),
                   PACKET_remaining(&prime), NULL)) == NULL
        || (s->srp_ctx.g =
            BN_bin2bn(PACKET_data(&generator),
                      PACKET_remaining(&generator), NULL)) == NULL
        || (s->srp_ctx.s =
            BN_bin2bn(PACKET_data(&salt),
                      PACKET_remaining(&salt), NULL)) == NULL
        || (s->srp_ctx.B =
            BN_bin2bn(PACKET_data(&server_pub),
                      PACKET_remaining(&server_pub), NULL)) == NULL) {
        *al = SSL_AD_INTERNAL_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_SKE_SRP, ERR_R_BN_LIB);
        return 0;
    }

    if (!srp_verify_server_param(s, al)) {
        *al = SSL_AD_DECODE_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_SKE_SRP, SSL_R_BAD_SRP_PARAMETERS);
        return 0;
    }

    /* We must check if there is a certificate */
    if (s->s3->tmp.new_cipher->algorithm_auth & (SSL_aRSA | SSL_aDSS))
        *pkey = X509_get0_pubkey(s->session->peer);

    return 1;
#else
    SSLerr(SSL_F_TLS_PROCESS_SKE_SRP, ERR_R_INTERNAL_ERROR);
    *al = SSL_AD_INTERNAL_ERROR;
    return 0;
#endif
}
