pdf_copy_array(fz_context *ctx, pdf_obj *obj)
{
	pdf_document *doc;
	pdf_obj *arr;
	int i;
	int n;

	RESOLVE(obj);
	if (!OBJ_IS_ARRAY(obj))
		fz_throw(ctx, FZ_ERROR_GENERIC, "not an array (%s)", pdf_objkindstr(obj));

	doc = ARRAY(obj)->doc;

	n = pdf_array_len(ctx, obj);
	arr = pdf_new_array(ctx, doc, n);
	for (i = 0; i < n; i++)
		pdf_array_push(ctx, arr, pdf_array_get(ctx, obj, i));

	return arr;
}
