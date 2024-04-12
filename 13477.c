static int fname_decrypt(struct inode *inode,
				const struct fscrypt_str *iname,
				struct fscrypt_str *oname)
{
	struct skcipher_request *req = NULL;
	DECLARE_FS_COMPLETION_RESULT(ecr);
	struct scatterlist src_sg, dst_sg;
	struct fscrypt_info *ci = inode->i_crypt_info;
	struct crypto_skcipher *tfm = ci->ci_ctfm;
	int res = 0;
	char iv[FS_CRYPTO_BLOCK_SIZE];
	unsigned lim;

	lim = inode->i_sb->s_cop->max_namelen(inode);
	if (iname->len <= 0 || iname->len > lim)
		return -EIO;

	/* Allocate request */
	req = skcipher_request_alloc(tfm, GFP_NOFS);
	if (!req) {
		printk_ratelimited(KERN_ERR
			"%s: crypto_request_alloc() failed\n",  __func__);
		return -ENOMEM;
	}
	skcipher_request_set_callback(req,
		CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
		fname_crypt_complete, &ecr);

	/* Initialize IV */
	memset(iv, 0, FS_CRYPTO_BLOCK_SIZE);

	/* Create decryption request */
	sg_init_one(&src_sg, iname->name, iname->len);
	sg_init_one(&dst_sg, oname->name, oname->len);
	skcipher_request_set_crypt(req, &src_sg, &dst_sg, iname->len, iv);
	res = crypto_skcipher_decrypt(req);
	if (res == -EINPROGRESS || res == -EBUSY) {
		wait_for_completion(&ecr.completion);
		res = ecr.res;
	}
	skcipher_request_free(req);
	if (res < 0) {
		printk_ratelimited(KERN_ERR
				"%s: Error (error code %d)\n", __func__, res);
		return res;
	}

	oname->len = strnlen(oname->name, iname->len);
	return 0;
}
