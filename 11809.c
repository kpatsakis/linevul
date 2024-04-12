rfc4106_set_hash_subkey(u8 *hash_subkey, const u8 *key, unsigned int key_len)
{
	struct crypto_ablkcipher *ctr_tfm;
	struct ablkcipher_request *req;
	int ret = -EINVAL;
	struct aesni_hash_subkey_req_data *req_data;

	ctr_tfm = crypto_alloc_ablkcipher("ctr(aes)", 0, 0);
	if (IS_ERR(ctr_tfm))
		return PTR_ERR(ctr_tfm);

	crypto_ablkcipher_clear_flags(ctr_tfm, ~0);

	ret = crypto_ablkcipher_setkey(ctr_tfm, key, key_len);
	if (ret)
		goto out_free_ablkcipher;

	ret = -ENOMEM;
	req = ablkcipher_request_alloc(ctr_tfm, GFP_KERNEL);
	if (!req)
		goto out_free_ablkcipher;

	req_data = kmalloc(sizeof(*req_data), GFP_KERNEL);
	if (!req_data)
		goto out_free_request;

	memset(req_data->iv, 0, sizeof(req_data->iv));

	/* Clear the data in the hash sub key container to zero.*/
	/* We want to cipher all zeros to create the hash sub key. */
	memset(hash_subkey, 0, RFC4106_HASH_SUBKEY_SIZE);

	init_completion(&req_data->result.completion);
	sg_init_one(&req_data->sg, hash_subkey, RFC4106_HASH_SUBKEY_SIZE);
	ablkcipher_request_set_tfm(req, ctr_tfm);
	ablkcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP |
					CRYPTO_TFM_REQ_MAY_BACKLOG,
					rfc4106_set_hash_subkey_done,
					&req_data->result);

	ablkcipher_request_set_crypt(req, &req_data->sg,
		&req_data->sg, RFC4106_HASH_SUBKEY_SIZE, req_data->iv);

	ret = crypto_ablkcipher_encrypt(req);
	if (ret == -EINPROGRESS || ret == -EBUSY) {
		ret = wait_for_completion_interruptible
			(&req_data->result.completion);
		if (!ret)
			ret = req_data->result.err;
	}
	kfree(req_data);
out_free_request:
	ablkcipher_request_free(req);
out_free_ablkcipher:
	crypto_free_ablkcipher(ctr_tfm);
	return ret;
}
