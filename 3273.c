static int __init camellia_init(void)
{
	return crypto_register_alg(&camellia_alg);
}
