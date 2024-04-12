pgp_get_pubkey(sc_card_t *card, unsigned int tag, u8 *buf, size_t buf_len)
{
	sc_apdu_t	apdu;
	u8 apdu_case = (card->type == SC_CARD_TYPE_OPENPGP_GNUK)
			? SC_APDU_CASE_4_SHORT : SC_APDU_CASE_4;
	u8		idbuf[2];
	int		r;

	sc_log(card->ctx, "called, tag=%04x\n", tag);

	sc_format_apdu(card, &apdu, apdu_case, 0x47, 0x81, 0);
	apdu.lc = 2;
	apdu.data = ushort2bebytes(idbuf, tag);
	apdu.datalen = 2;
	apdu.le = ((buf_len >= 256) && !(card->caps & SC_CARD_CAP_APDU_EXT)) ? 256 : buf_len;
	apdu.resp = buf;
	apdu.resplen = buf_len;

	r = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, r, "APDU transmit failed");

	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(card->ctx, r, "Card returned error");

	LOG_FUNC_RETURN(card->ctx, (int)apdu.resplen);
}
