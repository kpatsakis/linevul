int i2d_RSAPrivateKey_fp(FILE *fp, RSA *rsa)
	{
	return ASN1_item_i2d_fp(ASN1_ITEM_rptr(RSAPrivateKey), fp, rsa);
	}
