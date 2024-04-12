int skcipher_walk_aead_decrypt(struct skcipher_walk *walk,
			       struct aead_request *req, bool atomic)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);

	walk->total = req->cryptlen - crypto_aead_authsize(tfm);

	return skcipher_walk_aead_common(walk, req, atomic);
}
