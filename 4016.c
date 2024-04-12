static IW_INLINE void put_raw_sample_16(struct iw_context *ctx, double s,
	   int x, int y, int channel)
{
	size_t z;
	unsigned short tmpui16;

	tmpui16 = (unsigned short)(0.5+s);
	z = y*ctx->img2.bpr + (ctx->img2_numchannels*x + channel)*2;
	ctx->img2.pixels[z+0] = (iw_byte)(tmpui16>>8);
	ctx->img2.pixels[z+1] = (iw_byte)(tmpui16&0xff);
}
