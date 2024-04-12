X509 *d2i_X509_bio(BIO *bp, X509 **x509)
	{
	return ASN1_item_d2i_bio(ASN1_ITEM_rptr(X509), bp, x509);
	}
