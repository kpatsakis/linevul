pdf_init_csi(fz_context *ctx, pdf_csi *csi, pdf_document *doc, pdf_obj *rdb, pdf_lexbuf *buf, fz_cookie *cookie)
{
	memset(csi, 0, sizeof *csi);
	csi->doc = doc;
	csi->rdb = rdb;
	csi->buf = buf;
	csi->cookie = cookie;
}
