gpk_decipher(sc_card_t *card, const u8 *in, size_t inlen,
		u8 *out, size_t outlen)
{
	struct gpk_private_data *priv = DRVDATA(card);
	sc_apdu_t	apdu;
	u8		buffer[256];
	int		r;

	if (inlen != priv->sec_mod_len) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL,
			 "Data length (%"SC_FORMAT_LEN_SIZE_T"u) does not match key modulus %u.\n",
			 inlen, priv->sec_mod_len);
		return SC_ERROR_INVALID_ARGUMENTS;
	}

	/* First revert the cryptogram */
	r = reverse(buffer, sizeof(buffer), in, inlen);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Cryptogram too large");
	in = buffer;

	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x1C, 0x00, 0x00);
	apdu.cla |= 0x80;
	apdu.lc   = inlen;
	apdu.data = in;
	apdu.datalen = inlen;
	apdu.le   = 256;		/* give me all you got :) */
	apdu.resp = buffer;
	apdu.resplen = sizeof(buffer);

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Card returned error");

	/* Reverse the data we got back */
	r = reverse(out, outlen, buffer, apdu.resplen);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Failed to reverse buffer");

	return r;
}
