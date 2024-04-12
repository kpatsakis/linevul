IW_IMPL(void) iw_set_resize_alg(struct iw_context *ctx, int dimension, int family,
    double blur, double param1, double param2)
{
	struct iw_resize_settings *rs;

	if(dimension<0 || dimension>1) dimension=0;
	rs=&ctx->resize_settings[dimension];

	rs->family = family;
	rs->blur_factor = blur;
	rs->param1 = param1;
	rs->param2 = param2;
}
