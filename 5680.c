int i2d_RSAPrivateKey_bio(BIO *bp, RSA *rsa)
	{
	return ASN1_item_i2d_bio(ASN1_ITEM_rptr(RSAPrivateKey), bp, rsa);
	}
