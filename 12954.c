pgp_put_data_plain(sc_card_t *card, unsigned int tag, const u8 *buf, size_t buf_len)
{
	struct pgp_priv_data *priv = DRVDATA(card);
	sc_apdu_t apdu;
	u8 ins = 0xDA;
	u8 p1 = tag >> 8;
	u8 p2 = tag & 0xFF;
	u8 apdu_case = (card->type == SC_CARD_TYPE_OPENPGP_GNUK)
			? SC_APDU_CASE_3_SHORT : SC_APDU_CASE_3;
	int r;

	LOG_FUNC_CALLED(card->ctx);

	/* Extended Header list (DO 004D) needs a variant of PUT DATA command */
	if (tag == 0x004D) {
		ins = 0xDB;
		p1 = 0x3F;
		p2 = 0xFF;
	}

	/* build APDU */
	if (buf != NULL && buf_len > 0) {
		sc_format_apdu(card, &apdu, apdu_case, ins, p1, p2);

		/* if card/reader does not support extended APDUs, but chaining, then set it */
		if (((card->caps & SC_CARD_CAP_APDU_EXT) == 0) && (priv->ext_caps & EXT_CAP_CHAINING))
			apdu.flags |= SC_APDU_FLAGS_CHAINING;

		apdu.data = (u8 *)buf;
		apdu.datalen = buf_len;
		apdu.lc = buf_len;
	}
	else {
		/* This case is to empty DO */
		sc_format_apdu(card, &apdu, SC_APDU_CASE_1, ins, p1, p2);
	}

	/* send APDU to card */
	r = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, r, "APDU transmit failed");
	/* check response */
	r = sc_check_sw(card, apdu.sw1, apdu.sw2);

	if (r < 0)
		LOG_FUNC_RETURN(card->ctx, r);

	LOG_FUNC_RETURN(card->ctx, (int)buf_len);
}
