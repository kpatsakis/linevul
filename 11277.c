static int jp2_ihdr_putdata(jp2_box_t *box, jas_stream_t *out)
{
	jp2_ihdr_t *ihdr = &box->data.ihdr;
	if (jp2_putuint32(out, ihdr->height) || jp2_putuint32(out, ihdr->width) ||
	  jp2_putuint16(out, ihdr->numcmpts) || jp2_putuint8(out, ihdr->bpc) ||
	  jp2_putuint8(out, ihdr->comptype) || jp2_putuint8(out, ihdr->csunk) ||
	  jp2_putuint8(out, ihdr->ipr)) {
		return -1;
	}
	return 0;
}
