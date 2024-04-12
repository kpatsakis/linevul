pdf_drop_xobject(fz_context *ctx, pdf_xobject *xobj)
{
	fz_drop_storable(ctx, &xobj->storable);
}
