char * SRP_check_known_gN_param(BIGNUM* g, BIGNUM* N)
	{
	size_t i;
	if ((g == NULL) || (N == NULL))
		return 0;

	srp_bn_print(g);
	srp_bn_print(N);

	for(i = 0; i < KNOWN_GN_NUMBER; i++)
		{
		if (BN_cmp(knowngN[i].g, g) == 0 && BN_cmp(knowngN[i].N, N) == 0) 
			return knowngN[i].id;
		}
	return NULL;
	}
