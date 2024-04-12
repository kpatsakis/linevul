PKCS7 *d2i_PKCS7_fp(FILE *fp, PKCS7 **p7)
	{
	return ASN1_item_d2i_fp(ASN1_ITEM_rptr(PKCS7), fp, p7);
	}
