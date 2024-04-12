authentic_manage_sdo_generate(struct sc_card *card, struct sc_authentic_sdo *sdo)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu apdu;
	unsigned char rbuf[0x400];
	unsigned char *data = NULL;
	size_t data_len = 0;
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "Generate SDO(mech:%X,id:%X)",  sdo->docp.mech, sdo->docp.id);

	rv = authentic_manage_sdo_encode(card, sdo, SC_CARDCTL_AUTHENTIC_SDO_GENERATE, &data, &data_len);
	LOG_TEST_RET(ctx, rv, "Cannot encode SDO data");
	sc_log(ctx, "encoded SDO length %"SC_FORMAT_LEN_SIZE_T"u", data_len);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x47, 0x00, 0x00);
	apdu.data = data;
	apdu.datalen = data_len;
	apdu.lc = data_len;
	apdu.resp = rbuf;
        apdu.resplen = sizeof(rbuf);
	apdu.le = 0x100;

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(ctx, rv, "authentic_sdo_create() SDO put data error");

	rv = authentic_decode_pubkey_rsa(ctx, apdu.resp, apdu.resplen, &sdo->data.prvkey);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, rv, "cannot decode public key");

	free(data);
	LOG_FUNC_RETURN(ctx, rv);
}
