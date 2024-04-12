pdf_keep_document(fz_context *ctx, pdf_document *doc)
{
	return (pdf_document *)fz_keep_document(ctx, &doc->super);
}
