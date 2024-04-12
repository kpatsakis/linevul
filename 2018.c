int test_probable_prime_coprime(BIO *bp, BN_CTX *ctx)
	{
	int i, j, ret = 0;
	BIGNUM r;
	BN_ULONG primes[5] = { 2, 3, 5, 7, 11 };

	BN_init(&r);
	
	for (i = 0; i < 1000; i++)
		{
		if (!bn_probable_prime_dh_coprime(&r, 1024, ctx)) goto err;
		
		for (j = 0; j < 5; j++)
			{
			if (BN_mod_word(&r, primes[j]) == 0)
				{
				BIO_printf(bp, "Number generated is not coprime to %ld:\n", primes[j]);
				BN_print_fp(stdout, &r);
				BIO_printf(bp, "\n");
				goto err;
				}
			}
		}

	ret = 1;

err:
	BN_clear(&r);
	return ret;
	}
