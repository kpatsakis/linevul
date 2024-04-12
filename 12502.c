static void iw_set_auto_resizetype(struct iw_context *ctx, int size1, int size2,
	int dimension)
{
	if(size2==size1 && !ctx->resize_settings[dimension].use_offset &&
		!ctx->req.out_true_valid &&
		ctx->resize_settings[dimension].translate==0.0)
	{
		iw_set_resize_alg(ctx, dimension, IW_RESIZETYPE_NULL, 1.0, 0.0, 0.0);
		return;
	}

	iw_set_resize_alg(ctx, dimension, IW_RESIZETYPE_CUBIC, 1.0, 0.0, 0.5);
}
