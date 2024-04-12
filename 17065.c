BIGNUM *SRP_Calc_server_key(BIGNUM *A, BIGNUM *v, BIGNUM *u, BIGNUM *b, BIGNUM *N)
	{
	BIGNUM *tmp = NULL, *S = NULL;
	BN_CTX *bn_ctx; 
	
	if (u == NULL || A == NULL || v == NULL || b == NULL || N == NULL)
		return NULL; 

	if ((bn_ctx = BN_CTX_new()) == NULL ||
		(tmp = BN_new()) == NULL ||
		(S = BN_new()) == NULL )
		goto err;

	/* S = (A*v**u) ** b */ 

	if (!BN_mod_exp(tmp,v,u,N,bn_ctx))
		goto err;
	if (!BN_mod_mul(tmp,A,tmp,N,bn_ctx))
		goto err;
	if (!BN_mod_exp(S,tmp,b,N,bn_ctx))
		goto err;
err:
	BN_CTX_free(bn_ctx);
	BN_clear_free(tmp);
	return S;
	}
