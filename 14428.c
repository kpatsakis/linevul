int pdf_xobject_transparency(fz_context *ctx, pdf_xobject *xobj)
{
	pdf_obj *group = pdf_dict_get(ctx, xobj->obj, PDF_NAME_Group);
	if (group)
		if (pdf_name_eq(ctx, pdf_dict_get(ctx, group, PDF_NAME_S), PDF_NAME_Transparency))
			return 1;
	return 0;
}
