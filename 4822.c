static int setkey_fallback_cip(struct crypto_tfm *tfm, const u8 *in_key,
		unsigned int key_len)
{
	struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);
	int ret;

	sctx->fallback.cip->base.crt_flags &= ~CRYPTO_TFM_REQ_MASK;
	sctx->fallback.cip->base.crt_flags |= (tfm->crt_flags &
			CRYPTO_TFM_REQ_MASK);

	ret = crypto_cipher_setkey(sctx->fallback.cip, in_key, key_len);
	if (ret) {
		tfm->crt_flags &= ~CRYPTO_TFM_RES_MASK;
		tfm->crt_flags |= (sctx->fallback.cip->base.crt_flags &
				CRYPTO_TFM_RES_MASK);
	}
	return ret;
}
