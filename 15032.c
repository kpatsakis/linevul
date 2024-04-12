static void __exit cleanup_encrypted(void)
{
	crypto_free_shash(hash_tfm);
	unregister_key_type(&key_type_encrypted);
}
