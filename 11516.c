piv_put_data(sc_card_t *card, int tag, const u8 *buf, size_t buf_len)
{
	int r;
	u8 * sbuf;
	size_t sbuflen;
	u8 * p;
	size_t tag_len;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	tag_len = piv_objects[tag].tag_len;
	sbuflen = put_tag_and_len(0x5c, tag_len, NULL) + buf_len;
	if (!(sbuf = malloc(sbuflen)))
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_OUT_OF_MEMORY);

	p = sbuf;
	put_tag_and_len(0x5c, tag_len, &p);
	memcpy(p, piv_objects[tag].tag_value, tag_len);
	p += tag_len;

	memcpy(p, buf, buf_len);
	p += buf_len;

	r = piv_general_io(card, 0xDB, 0x3F, 0xFF, sbuf, p - sbuf, NULL, NULL);

	if (sbuf)
		free(sbuf);
	LOG_FUNC_RETURN(card->ctx, r);
}
