static int big_key_crypt(enum big_key_op op, u8 *data, size_t datalen, u8 *key)
{
	int ret = -EINVAL;
	struct scatterlist sgio;
	SKCIPHER_REQUEST_ON_STACK(req, big_key_skcipher);

	if (crypto_skcipher_setkey(big_key_skcipher, key, ENC_KEY_SIZE)) {
		ret = -EAGAIN;
		goto error;
	}

	skcipher_request_set_tfm(req, big_key_skcipher);
	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP,
				      NULL, NULL);

	sg_init_one(&sgio, data, datalen);
	skcipher_request_set_crypt(req, &sgio, &sgio, datalen, NULL);

	if (op == BIG_KEY_ENC)
		ret = crypto_skcipher_encrypt(req);
	else
		ret = crypto_skcipher_decrypt(req);

	skcipher_request_zero(req);

error:
	return ret;
}
