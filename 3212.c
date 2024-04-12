static int asepcos_activate_file(sc_card_t *card, int fileid, int is_ef)
{
	int r, type = is_ef != 0 ? 2 : 1;
	sc_apdu_t apdu;
	u8 sbuf[2];

	sbuf[0] = (fileid >> 8) & 0xff;
	sbuf[1] = fileid & 0xff;
	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x44, type, 0x00);
	apdu.lc      = 2;
	apdu.datalen = 2;
	apdu.data    = sbuf;
	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	return sc_check_sw(card, apdu.sw1, apdu.sw2);
} 
