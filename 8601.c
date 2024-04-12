static int rle_patch_file_size(struct iwbmpwcontext *wctx,size_t rlesize)
{
	iw_byte buf[4];
	size_t fileheader_size;
	int ret;

	if(!wctx->iodescr->seek_fn) {
		iw_set_error(wctx->ctx,"Writing compressed BMP requires a seek function");
		return 0;
	}

	if(wctx->include_file_header) {
		ret=(*wctx->iodescr->seek_fn)(wctx->ctx,wctx->iodescr,2,SEEK_SET);
		if(!ret) return 0;
		iw_set_ui32le(buf,(unsigned int)(14+wctx->header_size+wctx->bitfields_size+wctx->palsize+rlesize));
		iwbmp_write(wctx,buf,4);
		fileheader_size = 14;
	}
	else {
		fileheader_size = 0;
	}

	ret=(*wctx->iodescr->seek_fn)(wctx->ctx,wctx->iodescr,fileheader_size+20,SEEK_SET);
	if(!ret) return 0;
	iw_set_ui32le(buf,(unsigned int)rlesize);
	iwbmp_write(wctx,buf,4);

	(*wctx->iodescr->seek_fn)(wctx->ctx,wctx->iodescr,0,SEEK_END);
	return 1;
}
