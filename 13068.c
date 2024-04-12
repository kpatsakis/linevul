static iw_tmpsample get_raw_sample_flt32(struct iw_context *ctx,
	   int x, int y, int channel)
{
	size_t z;
	z = y*ctx->img1.bpr + (ctx->img1_numchannels_physical*x + channel)*4;
	return (iw_tmpsample)iw_get_float32(&ctx->img1.pixels[z]);
}
