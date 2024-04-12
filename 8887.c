static int ceph_aes_decrypt2(const void *key, int key_len,
			     void *dst1, size_t *dst1_len,
			     void *dst2, size_t *dst2_len,
			     const void *src, size_t src_len)
{
	struct sg_table sg_in;
	struct scatterlist sg_out[3], prealloc_sg;
	struct crypto_skcipher *tfm = ceph_crypto_alloc_cipher();
	SKCIPHER_REQUEST_ON_STACK(req, tfm);
	char pad[16];
	char iv[AES_BLOCK_SIZE];
	int ret;
	int last_byte;

	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	sg_init_table(sg_out, 3);
	sg_set_buf(&sg_out[0], dst1, *dst1_len);
	sg_set_buf(&sg_out[1], dst2, *dst2_len);
	sg_set_buf(&sg_out[2], pad, sizeof(pad));
	ret = setup_sgtable(&sg_in, &prealloc_sg, src, src_len);
	if (ret)
		goto out_tfm;

	crypto_skcipher_setkey((void *)tfm, key, key_len);
	memcpy(iv, aes_iv, AES_BLOCK_SIZE);

	skcipher_request_set_tfm(req, tfm);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, sg_in.sgl, sg_out,
				   src_len, iv);

	/*
	print_hex_dump(KERN_ERR, "dec  key: ", DUMP_PREFIX_NONE, 16, 1,
		       key, key_len, 1);
	print_hex_dump(KERN_ERR, "dec   in: ", DUMP_PREFIX_NONE, 16, 1,
		       src, src_len, 1);
	*/
	ret = crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);
	if (ret < 0) {
		pr_err("ceph_aes_decrypt failed %d\n", ret);
		goto out_sg;
	}

	if (src_len <= *dst1_len)
		last_byte = ((char *)dst1)[src_len - 1];
	else if (src_len <= *dst1_len + *dst2_len)
		last_byte = ((char *)dst2)[src_len - *dst1_len - 1];
	else
		last_byte = pad[src_len - *dst1_len - *dst2_len - 1];
	if (last_byte <= 16 && src_len >= last_byte) {
		src_len -= last_byte;
	} else {
		pr_err("ceph_aes_decrypt got bad padding %d on src len %d\n",
		       last_byte, (int)src_len);
		return -EPERM;  /* bad padding */
	}

	if (src_len < *dst1_len) {
		*dst1_len = src_len;
		*dst2_len = 0;
	} else {
		*dst2_len = src_len - *dst1_len;
	}
	/*
	print_hex_dump(KERN_ERR, "dec  out1: ", DUMP_PREFIX_NONE, 16, 1,
		       dst1, *dst1_len, 1);
	print_hex_dump(KERN_ERR, "dec  out2: ", DUMP_PREFIX_NONE, 16, 1,
		       dst2, *dst2_len, 1);
	*/

out_sg:
	teardown_sgtable(&sg_in);
out_tfm:
	crypto_free_skcipher(tfm);
	return ret;
}
