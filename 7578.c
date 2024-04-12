	fz_catch(ctx)
	{
		pdf_drop_obj(ctx, encrypt);
		pdf_drop_obj(ctx, id);
		pdf_drop_obj(ctx, obj);
		pdf_drop_obj(ctx, info);
		fz_free(ctx, list);
		fz_rethrow(ctx);
	}
