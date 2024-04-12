IW_IMPL(void) iw_set_apply_bkgd_2(struct iw_context *ctx, const struct iw_color *clr)
{
	ctx->req.bkgd_valid=1;
	ctx->req.bkgd = *clr;
}
