static int keyvalcmp(const void *ap, const void *bp)
{
	const struct keyval *a = ap;
	const struct keyval *b = bp;
	const char *an;
	const char *bn;

	/* We should never get a->k == NULL or b->k == NULL. If we
	 * do, then they match. */
	if (a->k < PDF_OBJ_NAME__LIMIT)
		an = PDF_NAMES[(intptr_t)a->k];
	else if (a->k >= PDF_OBJ__LIMIT && a->k->kind == PDF_NAME)
		an = NAME(a->k)->n;
	else
		return 0;

	if (b->k < PDF_OBJ_NAME__LIMIT)
		bn = PDF_NAMES[(intptr_t)b->k];
	else if (b->k >= PDF_OBJ__LIMIT && b->k->kind == PDF_NAME)
		bn = NAME(b->k)->n;
	else
		return 0;

	return strcmp(an, bn);
}
