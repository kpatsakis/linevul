X509_SIG *d2i_PKCS8_fp(FILE *fp, X509_SIG **p8)
	{
	return ASN1_d2i_fp_of(X509_SIG,X509_SIG_new,d2i_X509_SIG,fp,p8);
	}
