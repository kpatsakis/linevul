static void jp2_colr_dumpdata(jp2_box_t *box, FILE *out)
{
	jp2_colr_t *colr = &box->data.colr;
	fprintf(out, "method=%d; pri=%d; approx=%d\n", (int)colr->method, (int)colr->pri, (int)colr->approx);
	switch (colr->method) {
	case JP2_COLR_ENUM:
		fprintf(out, "csid=%d\n", (int)colr->csid);
		break;
	case JP2_COLR_ICC:
		jas_memdump(out, colr->iccp, colr->iccplen);
		break;
	}
}
