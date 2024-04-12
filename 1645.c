int ahash_mcryptd_digest(struct ahash_request *desc)
{
	return crypto_ahash_init(desc) ?: ahash_mcryptd_finup(desc);
}
