void mbedtls_ecdsa_init( mbedtls_ecdsa_context *ctx )
{
    mbedtls_ecp_keypair_init( ctx );
}
