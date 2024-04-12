int mbedtls_ecp_self_test( int verbose )
{
    int ret;
    size_t i;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point R, P;
    mbedtls_mpi m;
    unsigned long add_c_prev, dbl_c_prev, mul_c_prev;
    /* exponents especially adapted for secp192r1 */
    const char *exponents[] =
    {
        "000000000000000000000000000000000000000000000001", /* one */
        "FFFFFFFFFFFFFFFFFFFFFFFF99DEF836146BC9B1B4D22830", /* N - 1 */
        "5EA6F389A38B8BC81E767753B15AA5569E1782E30ABE7D25", /* random */
        "400000000000000000000000000000000000000000000000", /* one and zeros */
        "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", /* all ones */
        "555555555555555555555555555555555555555555555555", /* 101010... */
    };

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &R );
    mbedtls_ecp_point_init( &P );
    mbedtls_mpi_init( &m );

    /* Use secp192r1 if available, or any available curve */
#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
    MBEDTLS_MPI_CHK( mbedtls_ecp_group_load( &grp, MBEDTLS_ECP_DP_SECP192R1 ) );
#else
    MBEDTLS_MPI_CHK( mbedtls_ecp_group_load( &grp, mbedtls_ecp_curve_list()->grp_id ) );
#endif

    if( verbose != 0 )
        mbedtls_printf( "  ECP test #1 (constant op_count, base point G): " );

    /* Do a dummy multiplication first to trigger precomputation */
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &m, 2 ) );
    MBEDTLS_MPI_CHK( mbedtls_ecp_mul( &grp, &P, &m, &grp.G, NULL, NULL ) );

    add_count = 0;
    dbl_count = 0;
    mul_count = 0;
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &m, 16, exponents[0] ) );
    MBEDTLS_MPI_CHK( mbedtls_ecp_mul( &grp, &R, &m, &grp.G, NULL, NULL ) );

    for( i = 1; i < sizeof( exponents ) / sizeof( exponents[0] ); i++ )
    {
        add_c_prev = add_count;
        dbl_c_prev = dbl_count;
        mul_c_prev = mul_count;
        add_count = 0;
        dbl_count = 0;
        mul_count = 0;

        MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &m, 16, exponents[i] ) );
        MBEDTLS_MPI_CHK( mbedtls_ecp_mul( &grp, &R, &m, &grp.G, NULL, NULL ) );

        if( add_count != add_c_prev ||
            dbl_count != dbl_c_prev ||
            mul_count != mul_c_prev )
        {
            if( verbose != 0 )
                mbedtls_printf( "failed (%u)\n", (unsigned int) i );

            ret = 1;
            goto cleanup;
        }
    }

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

    if( verbose != 0 )
        mbedtls_printf( "  ECP test #2 (constant op_count, other point): " );
    /* We computed P = 2G last time, use it */

    add_count = 0;
    dbl_count = 0;
    mul_count = 0;
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &m, 16, exponents[0] ) );
    MBEDTLS_MPI_CHK( mbedtls_ecp_mul( &grp, &R, &m, &P, NULL, NULL ) );

    for( i = 1; i < sizeof( exponents ) / sizeof( exponents[0] ); i++ )
    {
        add_c_prev = add_count;
        dbl_c_prev = dbl_count;
        mul_c_prev = mul_count;
        add_count = 0;
        dbl_count = 0;
        mul_count = 0;

        MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &m, 16, exponents[i] ) );
        MBEDTLS_MPI_CHK( mbedtls_ecp_mul( &grp, &R, &m, &P, NULL, NULL ) );

        if( add_count != add_c_prev ||
            dbl_count != dbl_c_prev ||
            mul_count != mul_c_prev )
        {
            if( verbose != 0 )
                mbedtls_printf( "failed (%u)\n", (unsigned int) i );

            ret = 1;
            goto cleanup;
        }
    }

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

cleanup:

    if( ret < 0 && verbose != 0 )
        mbedtls_printf( "Unexpected error, return code = %08X\n", ret );

    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &R );
    mbedtls_ecp_point_free( &P );
    mbedtls_mpi_free( &m );

    if( verbose != 0 )
        mbedtls_printf( "\n" );

    return( ret );
}
