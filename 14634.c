int X509_CRL_sign_ctx(X509_CRL *x, EVP_MD_CTX *ctx)
	{
	x->crl->enc.modified = 1;
	return ASN1_item_sign_ctx(ASN1_ITEM_rptr(X509_CRL_INFO),
		x->crl->sig_alg, x->sig_alg, x->signature, x->crl, ctx);
	}
