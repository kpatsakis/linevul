static int sha1_export(struct shash_desc *desc, void *out)
{
	struct s390_sha_ctx *sctx = shash_desc_ctx(desc);
	struct sha1_state *octx = out;

	octx->count = sctx->count;
	memcpy(octx->state, sctx->state, sizeof(octx->state));
	memcpy(octx->buffer, sctx->buf, sizeof(octx->buffer));
	return 0;
}
