pdf_dict_geta(fz_context *ctx, pdf_obj *obj, pdf_obj *key, pdf_obj *abbrev)
{
	pdf_obj *v;
	v = pdf_dict_get(ctx, obj, key);
	if (v)
		return v;
        return pdf_dict_get(ctx, obj, abbrev);
 }
