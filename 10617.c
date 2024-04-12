IW_IMPL(int) iw_read_gif_file(struct iw_context *ctx, struct iw_iodescr *iodescr)
{
	struct iw_image img;
	struct iwgifrcontext *rctx = NULL;
	int retval=0;

	iw_zeromem(&img,sizeof(struct iw_image));
	rctx = iw_mallocz(ctx,sizeof(struct iwgifrcontext));
	if(!rctx) goto done;

	rctx->ctx = ctx;
	rctx->iodescr = iodescr;
	rctx->img = &img;

	iw_make_srgb_csdescr_2(&rctx->csdescr);

	rctx->page = iw_get_value(ctx,IW_VAL_PAGE_TO_READ);
	if(rctx->page<1) rctx->page = 1;

	rctx->include_screen = iw_get_value(ctx,IW_VAL_INCLUDE_SCREEN);

	if(!iwgif_read_main(rctx))
		goto done;

	iw_set_input_image(ctx, &img);

	iw_set_input_colorspace(ctx,&rctx->csdescr);

	retval = 1;

done:
	if(!retval) {
		iw_set_error(ctx,"Failed to read GIF file");
	}

	if(rctx) {
		if(rctx->row_pointers) iw_free(ctx,rctx->row_pointers);
		iw_free(ctx,rctx);
	}

	return retval;
}
