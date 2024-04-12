authentic_get_challenge(struct sc_card *card, unsigned char *rnd, size_t len)
{
	/* 'GET CHALLENGE' returns always 24 bytes */
	unsigned char rbuf[0x18];
	size_t out_len;
	int r;

	LOG_FUNC_CALLED(card->ctx);

	r = iso_ops->get_challenge(card, rbuf, sizeof rbuf);
	LOG_TEST_RET(card->ctx, r, "GET CHALLENGE cmd failed");

	if (len < (size_t) r) {
		out_len = len;
	} else {
		out_len = (size_t) r;
	}
	memcpy(rnd, rbuf, out_len);

	LOG_FUNC_RETURN(card->ctx, out_len);
}
