int i2d_PKCS8_fp(FILE *fp, X509_SIG *p8)
	{
	return ASN1_i2d_fp_of(X509_SIG,i2d_X509_SIG,fp,p8);
	}
