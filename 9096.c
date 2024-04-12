int test_mod_exp_mont_consttime(BIO *bp, BN_CTX *ctx)
	{
	BIGNUM *a,*b,*c,*d,*e;
	int i;

	a=BN_new();
	b=BN_new();
	c=BN_new();
	d=BN_new();
	e=BN_new();

	BN_bntest_rand(c,30,0,1); /* must be odd for montgomery */
	for (i=0; i<num2; i++)
		{
		BN_bntest_rand(a,20+i*5,0,0); /**/
		BN_bntest_rand(b,2+i,0,0); /**/

		if (!BN_mod_exp_mont_consttime(d,a,b,c,ctx,NULL))
			return(00);

		if (bp != NULL)
			{
			if (!results)
				{
				BN_print(bp,a);
				BIO_puts(bp," ^ ");
				BN_print(bp,b);
				BIO_puts(bp," % ");
				BN_print(bp,c);
				BIO_puts(bp," - ");
				}
			BN_print(bp,d);
			BIO_puts(bp,"\n");
			}
		BN_exp(e,a,b,ctx);
		BN_sub(e,e,d);
		BN_div(a,b,e,c,ctx);
		if(!BN_is_zero(b))
		    {
		    fprintf(stderr,"Modulo exponentiation test failed!\n");
		    return 0;
		    }
		}
	BN_free(a);
	BN_free(b);
	BN_free(c);
	BN_free(d);
	BN_free(e);
	return(1);
	}
