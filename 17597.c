static void gcm_enc_copy_hash(struct aead_request *req,
			      struct crypto_gcm_req_priv_ctx *pctx)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	u8 *auth_tag = pctx->auth_tag;

	scatterwalk_map_and_copy(auth_tag, req->dst, req->cryptlen,
				 crypto_aead_authsize(aead), 1);
}
