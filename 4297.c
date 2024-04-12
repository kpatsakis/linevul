static int decode_v2_header(struct iwbmprcontext *rctx, const iw_byte *buf)
{
	unsigned int nplanes;

	rctx->width = iw_get_ui16le(&buf[4]);
	rctx->height = iw_get_ui16le(&buf[6]);
	nplanes = iw_get_ui16le(&buf[8]);
	if(nplanes!=1) return 0;
	rctx->bitcount = iw_get_ui16le(&buf[10]);
	if(rctx->bitcount!=1 && rctx->bitcount!=4 &&
		rctx->bitcount!=8 && rctx->bitcount!=24)
	{
		return 0;
	}
	if(rctx->bitcount<=8) {
		size_t palette_start, palette_end;

		rctx->palette_entries = 1<<rctx->bitcount;
		rctx->palette_nbytes = 3*rctx->palette_entries;

		palette_start = rctx->fileheader_size + rctx->infoheader_size;
		palette_end = palette_start + rctx->palette_nbytes;
		if(rctx->bfOffBits >= palette_start+3 && rctx->bfOffBits < palette_end) {
			rctx->palette_entries = (unsigned int)((rctx->bfOffBits - palette_start)/3);
			rctx->palette_nbytes = 3*rctx->palette_entries;
		}
	}
	return 1;
}
