size_t rand_acquire_entropy_from_cpu(RAND_POOL *pool)
{
    size_t bytes_needed;
    unsigned char *buffer;

    bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
    if (bytes_needed > 0) {
        buffer = rand_pool_add_begin(pool, bytes_needed);

        if (buffer != NULL) {
            /* Whichever comes first, use RDSEED, RDRAND or nothing */
            if ((OPENSSL_ia32cap_P[2] & (1 << 18)) != 0) {
                if (OPENSSL_ia32_rdseed_bytes(buffer, bytes_needed)
                    == bytes_needed) {
                    rand_pool_add_end(pool, bytes_needed, 8 * bytes_needed);
                }
            } else if ((OPENSSL_ia32cap_P[1] & (1 << (62 - 32))) != 0) {
                if (OPENSSL_ia32_rdrand_bytes(buffer, bytes_needed)
                    == bytes_needed) {
                    rand_pool_add_end(pool, bytes_needed, 8 * bytes_needed);
                }
            } else {
                rand_pool_add_end(pool, 0, 0);
            }
        }
    }

    return rand_pool_entropy_available(pool);
}
