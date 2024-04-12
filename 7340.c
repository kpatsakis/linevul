server_check_dh(krb5_context context,
                pkinit_plg_crypto_context cryptoctx,
                pkinit_req_crypto_context req_cryptoctx,
                pkinit_identity_crypto_context id_cryptoctx,
                krb5_data *dh_params,
                int minbits)
{
    DH *dh = NULL;
    const BIGNUM *p;
    int dh_prime_bits;
    krb5_error_code retval = KRB5KDC_ERR_DH_KEY_PARAMETERS_NOT_ACCEPTED;

    dh = decode_dh_params((uint8_t *)dh_params->data, dh_params->length);
    if (dh == NULL) {
        pkiDebug("failed to decode dhparams\n");
        goto cleanup;
    }

    /* KDC SHOULD check to see if the key parameters satisfy its policy */
    DH_get0_pqg(dh, &p, NULL, NULL);
    dh_prime_bits = BN_num_bits(p);
    if (minbits && dh_prime_bits < minbits) {
        pkiDebug("client sent dh params with %d bits, we require %d\n",
                 dh_prime_bits, minbits);
        goto cleanup;
    }

    if (check_dh_wellknown(cryptoctx, dh, dh_prime_bits))
        retval = 0;

cleanup:
    if (retval == 0)
        req_cryptoctx->dh = dh;
    else
        DH_free(dh);

    return retval;
}
