static int list_readers(void)
{
	unsigned int i, rcount = sc_ctx_get_reader_count(ctx);

	if (rcount == 0) {
		printf("No smart card readers found.\n");
		return 0;
	}
	printf("# Detected readers (%s)\n", ctx->reader_driver->short_name);
	printf("Nr.  Card  Features  Name\n");
	for (i = 0; i < rcount; i++) {
		sc_reader_t *reader = sc_ctx_get_reader(ctx, i);
		int state = sc_detect_card_presence(reader);
		printf("%-5d%-6s%-10s%s\n", i, state & SC_READER_CARD_PRESENT ? "Yes":"No",
		      reader->capabilities & SC_READER_CAP_PIN_PAD ? "PIN pad":"",
		      reader->name);
		if (state & SC_READER_CARD_PRESENT && verbose) {
			struct sc_card *card;
			int r;
			char tmp[SC_MAX_ATR_SIZE*3];
			sc_bin_to_hex(reader->atr.value, reader->atr.len, tmp, sizeof(tmp) - 1, ':');

			if (state & SC_READER_CARD_EXCLUSIVE)
				printf("     %s [EXCLUSIVE]\n", tmp);
			else {
				if ((r = sc_connect_card(reader, &card)) != SC_SUCCESS) {
					fprintf(stderr, "     failed: %s\n", sc_strerror(r));
				} else {
					printf("     %s %s %s\n", tmp, card->name ? card->name : "", state & SC_READER_CARD_INUSE ? "[IN USE]" : "");
					sc_disconnect_card(card);
				}
			}
		}
	}
	return 0;
}
