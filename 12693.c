static void crypto_gcm_free(struct crypto_instance *inst)
{
	struct gcm_instance_ctx *ctx = crypto_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->ctr);
	crypto_drop_ahash(&ctx->ghash);
	kfree(inst);
}
