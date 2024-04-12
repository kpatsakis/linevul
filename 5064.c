int pdf_xobject_isolated(fz_context *ctx, pdf_xobject *xobj)
{
	pdf_obj *group = pdf_dict_get(ctx, xobj->obj, PDF_NAME_Group);
	if (group)
		return pdf_to_bool(ctx, pdf_dict_get(ctx, group, PDF_NAME_I));
	return 0;
}
