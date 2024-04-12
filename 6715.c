static void __exit cast6_exit(void)
{
	crypto_unregister_algs(cast6_algs, ARRAY_SIZE(cast6_algs));
}
