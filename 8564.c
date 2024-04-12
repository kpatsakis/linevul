pdf_process_contents(fz_context *ctx, pdf_processor *proc, pdf_document *doc, pdf_obj *rdb, pdf_obj *stmobj, fz_cookie *cookie)
{
	pdf_csi csi;
	pdf_lexbuf buf;
	fz_stream *stm = NULL;

	if (!stmobj)
		return;

	fz_var(stm);

	pdf_lexbuf_init(ctx, &buf, PDF_LEXBUF_SMALL);
	pdf_init_csi(ctx, &csi, doc, rdb, &buf, cookie);

	fz_try(ctx)
	{
		fz_defer_reap_start(ctx);
		stm = pdf_open_contents_stream(ctx, doc, stmobj);
		pdf_process_stream(ctx, proc, &csi, stm);
		pdf_process_end(ctx, proc, &csi);
	}
	fz_always(ctx)
	{
		fz_defer_reap_end(ctx);
		fz_drop_stream(ctx, stm);
		pdf_clear_stack(ctx, &csi);
		pdf_lexbuf_fin(ctx, &buf);
	}
	fz_catch(ctx)
	{
		fz_rethrow(ctx);
	}
}
