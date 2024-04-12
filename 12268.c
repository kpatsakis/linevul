static int tls_process_cke_rsa(SSL *s, PACKET *pkt, int *al)
{
#ifndef OPENSSL_NO_RSA
    unsigned char rand_premaster_secret[SSL_MAX_MASTER_KEY_LENGTH];
    int decrypt_len;
    unsigned char decrypt_good, version_good;
    size_t j, padding_len;
    PACKET enc_premaster;
    RSA *rsa = NULL;
    unsigned char *rsa_decrypt = NULL;
    int ret = 0;

    rsa = EVP_PKEY_get0_RSA(s->cert->pkeys[SSL_PKEY_RSA_ENC].privatekey);
    if (rsa == NULL) {
        *al = SSL_AD_HANDSHAKE_FAILURE;
        SSLerr(SSL_F_TLS_PROCESS_CKE_RSA, SSL_R_MISSING_RSA_CERTIFICATE);
        return 0;
    }

    /* SSLv3 and pre-standard DTLS omit the length bytes. */
    if (s->version == SSL3_VERSION || s->version == DTLS1_BAD_VER) {
        enc_premaster = *pkt;
    } else {
        if (!PACKET_get_length_prefixed_2(pkt, &enc_premaster)
            || PACKET_remaining(pkt) != 0) {
            *al = SSL_AD_DECODE_ERROR;
            SSLerr(SSL_F_TLS_PROCESS_CKE_RSA, SSL_R_LENGTH_MISMATCH);
            return 0;
        }
    }

    /*
     * We want to be sure that the plaintext buffer size makes it safe to
     * iterate over the entire size of a premaster secret
     * (SSL_MAX_MASTER_KEY_LENGTH). Reject overly short RSA keys because
     * their ciphertext cannot accommodate a premaster secret anyway.
     */
    if (RSA_size(rsa) < SSL_MAX_MASTER_KEY_LENGTH) {
        *al = SSL_AD_INTERNAL_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CKE_RSA, RSA_R_KEY_SIZE_TOO_SMALL);
        return 0;
    }

    rsa_decrypt = OPENSSL_malloc(RSA_size(rsa));
    if (rsa_decrypt == NULL) {
        *al = SSL_AD_INTERNAL_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CKE_RSA, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    /*
     * We must not leak whether a decryption failure occurs because of
     * Bleichenbacher's attack on PKCS #1 v1.5 RSA padding (see RFC 2246,
     * section 7.4.7.1). The code follows that advice of the TLS RFC and
     * generates a random premaster secret for the case that the decrypt
     * fails. See https://tools.ietf.org/html/rfc5246#section-7.4.7.1
     */

    if (RAND_bytes(rand_premaster_secret, sizeof(rand_premaster_secret)) <= 0)
        goto err;

    /*
     * Decrypt with no padding. PKCS#1 padding will be removed as part of
     * the timing-sensitive code below.
     */
    decrypt_len = RSA_private_decrypt(PACKET_remaining(&enc_premaster),
                                      PACKET_data(&enc_premaster),
                                      rsa_decrypt, rsa, RSA_NO_PADDING);
    if (decrypt_len < 0)
        goto err;

    /* Check the padding. See RFC 3447, section 7.2.2. */

    /*
     * The smallest padded premaster is 11 bytes of overhead. Small keys
     * are publicly invalid, so this may return immediately. This ensures
     * PS is at least 8 bytes.
     */
    if (decrypt_len < 11 + SSL_MAX_MASTER_KEY_LENGTH) {
        *al = SSL_AD_DECRYPT_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CKE_RSA, SSL_R_DECRYPTION_FAILED);
        goto err;
    }

    padding_len = decrypt_len - SSL_MAX_MASTER_KEY_LENGTH;
    decrypt_good = constant_time_eq_int_8(rsa_decrypt[0], 0) &
        constant_time_eq_int_8(rsa_decrypt[1], 2);
    for (j = 2; j < padding_len - 1; j++) {
        decrypt_good &= ~constant_time_is_zero_8(rsa_decrypt[j]);
    }
    decrypt_good &= constant_time_is_zero_8(rsa_decrypt[padding_len - 1]);

    /*
     * If the version in the decrypted pre-master secret is correct then
     * version_good will be 0xff, otherwise it'll be zero. The
     * Klima-Pokorny-Rosa extension of Bleichenbacher's attack
     * (http://eprint.iacr.org/2003/052/) exploits the version number
     * check as a "bad version oracle". Thus version checks are done in
     * constant time and are treated like any other decryption error.
     */
    version_good =
        constant_time_eq_8(rsa_decrypt[padding_len],
                           (unsigned)(s->client_version >> 8));
    version_good &=
        constant_time_eq_8(rsa_decrypt[padding_len + 1],
                           (unsigned)(s->client_version & 0xff));

    /*
     * The premaster secret must contain the same version number as the
     * ClientHello to detect version rollback attacks (strangely, the
     * protocol does not offer such protection for DH ciphersuites).
     * However, buggy clients exist that send the negotiated protocol
     * version instead if the server does not support the requested
     * protocol version. If SSL_OP_TLS_ROLLBACK_BUG is set, tolerate such
     * clients.
     */
    if (s->options & SSL_OP_TLS_ROLLBACK_BUG) {
        unsigned char workaround_good;
        workaround_good = constant_time_eq_8(rsa_decrypt[padding_len],
                                             (unsigned)(s->version >> 8));
        workaround_good &=
            constant_time_eq_8(rsa_decrypt[padding_len + 1],
                               (unsigned)(s->version & 0xff));
        version_good |= workaround_good;
    }

    /*
     * Both decryption and version must be good for decrypt_good to
     * remain non-zero (0xff).
     */
    decrypt_good &= version_good;

    /*
     * Now copy rand_premaster_secret over from p using
     * decrypt_good_mask. If decryption failed, then p does not
     * contain valid plaintext, however, a check above guarantees
     * it is still sufficiently large to read from.
     */
    for (j = 0; j < sizeof(rand_premaster_secret); j++) {
        rsa_decrypt[padding_len + j] =
            constant_time_select_8(decrypt_good,
                                   rsa_decrypt[padding_len + j],
                                   rand_premaster_secret[j]);
    }

    if (!ssl_generate_master_secret(s, rsa_decrypt + padding_len,
                                    sizeof(rand_premaster_secret), 0)) {
        *al = SSL_AD_INTERNAL_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CKE_RSA, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    ret = 1;
 err:
    OPENSSL_free(rsa_decrypt);
    return ret;
#else
    /* Should never happen */
    *al = SSL_AD_INTERNAL_ERROR;
    SSLerr(SSL_F_TLS_PROCESS_CKE_RSA, ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}
