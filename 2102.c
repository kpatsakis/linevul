BOOL security_key_update(BYTE* key, BYTE* update_key, int key_len)
{
	BYTE sha1h[CRYPTO_SHA1_DIGEST_LENGTH];
	CryptoMd5 md5;
	CryptoSha1 sha1;
	CryptoRc4 rc4;
	BYTE salt40[] = { 0xD1, 0x26, 0x9E };

	sha1 = crypto_sha1_init();
	crypto_sha1_update(sha1, update_key, key_len);
	crypto_sha1_update(sha1, pad1, sizeof(pad1));
	crypto_sha1_update(sha1, key, key_len);
	crypto_sha1_final(sha1, sha1h);

	md5 = crypto_md5_init();
	crypto_md5_update(md5, update_key, key_len);
	crypto_md5_update(md5, pad2, sizeof(pad2));
	crypto_md5_update(md5, sha1h, sizeof(sha1h));
	crypto_md5_final(md5, key);

	rc4 = crypto_rc4_init(key, key_len);
	crypto_rc4(rc4, key_len, key, key);
	crypto_rc4_free(rc4);

	if (key_len == 8)
		memcpy(key, salt40, 3); /* TODO 56 bit */

	return TRUE;
}
