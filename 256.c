pdf_load_version(fz_context *ctx, pdf_document *doc)
{
	char buf[20];

	fz_seek(ctx, doc->file, 0, SEEK_SET);
	fz_read_line(ctx, doc->file, buf, sizeof buf);
	if (memcmp(buf, "%PDF-", 5) != 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot recognize version marker");

	doc->version = 10 * (fz_atof(buf+5) + 0.05f);
	if (doc->version < 10 || doc->version > 17)
		if (doc->version != 20)
			fz_warn(ctx, "unknown PDF version: %d.%d", doc->version / 10, doc->version % 10);
}
