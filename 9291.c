IW_IMPL(int) iw_write_bmp_file(struct iw_context *ctx, struct iw_iodescr *iodescr)
{
	struct iwbmpwcontext wctx;
	int retval=0;
	struct iw_image img1;

	iw_zeromem(&img1,sizeof(struct iw_image));

	iw_zeromem(&wctx,sizeof(struct iwbmpwcontext));

	wctx.ctx = ctx;
	wctx.include_file_header = 1;

	wctx.iodescr=iodescr;

	iw_get_output_image(ctx,&img1);
	wctx.img = &img1;

	if(wctx.img->imgtype==IW_IMGTYPE_PALETTE) {
		wctx.pal = iw_get_output_palette(ctx);
		if(!wctx.pal) goto done;
	}

	iw_get_output_colorspace(ctx,&wctx.csdescr);

	if(!iwbmp_write_main(&wctx)) {
		iw_set_error(ctx,"BMP write failed");
		goto done;
	}

	retval=1;

done:
	return retval;
}
