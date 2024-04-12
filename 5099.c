int i2d_PKCS7_bio(BIO *bp, PKCS7 *p7)
	{
	return ASN1_item_i2d_bio(ASN1_ITEM_rptr(PKCS7), bp, p7);
	}
