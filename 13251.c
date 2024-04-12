static int tls1_get_curvelist(SSL *s, int sess,
                              const unsigned char **pcurves,
                              size_t *num_curves)
{
    size_t pcurveslen = 0;
    if (sess) {
        *pcurves = s->session->tlsext_ellipticcurvelist;
        pcurveslen = s->session->tlsext_ellipticcurvelist_length;
    } else {
        /* For Suite B mode only include P-256, P-384 */
        switch (tls1_suiteb(s)) {
        case SSL_CERT_FLAG_SUITEB_128_LOS:
            *pcurves = suiteb_curves;
            pcurveslen = sizeof(suiteb_curves);
            break;

        case SSL_CERT_FLAG_SUITEB_128_LOS_ONLY:
            *pcurves = suiteb_curves;
            pcurveslen = 2;
            break;

        case SSL_CERT_FLAG_SUITEB_192_LOS:
            *pcurves = suiteb_curves + 2;
            pcurveslen = 2;
            break;
        default:
            *pcurves = s->tlsext_ellipticcurvelist;
            pcurveslen = s->tlsext_ellipticcurvelist_length;
        }
        if (!*pcurves) {
# ifdef OPENSSL_FIPS
            if (FIPS_mode()) {
                *pcurves = fips_curves_default;
                pcurveslen = sizeof(fips_curves_default);
            } else
# endif
            {
                if (!s->server || s->cert->ecdh_tmp_auto) {
                    *pcurves = eccurves_auto;
                    pcurveslen = sizeof(eccurves_auto);
                } else {
                    *pcurves = eccurves_all;
                    pcurveslen = sizeof(eccurves_all);
                }
            }
        }
    }
    /* We do not allow odd length arrays to enter the system. */
    if (pcurveslen & 1) {
        SSLerr(SSL_F_TLS1_GET_CURVELIST, ERR_R_INTERNAL_ERROR);
        *num_curves = 0;
        return 0;
    } else {
        *num_curves = pcurveslen / 2;
        return 1;
    }
}
