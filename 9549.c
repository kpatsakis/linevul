static int asepcos_init(sc_card_t *card)
{
	unsigned long	flags;

	card->name = "Athena ASEPCOS";
	card->cla  = 0x00;

	/* in case of a Java card try to select the ASEPCOS applet */
	if (card->type == SC_CARD_TYPE_ASEPCOS_JAVA) {
		int r = asepcos_select_asepcos_applet(card);
		if (r != SC_SUCCESS)
			return SC_ERROR_INVALID_CARD;
	}

	/* Set up algorithm info. */
	flags =	SC_ALGORITHM_RSA_RAW
		| SC_ALGORITHM_RSA_HASH_NONE
		| SC_ALGORITHM_ONBOARD_KEY_GEN
		;
	_sc_card_add_rsa_alg(card,  512, flags, 0);
	_sc_card_add_rsa_alg(card,  768, flags, 0);
	_sc_card_add_rsa_alg(card, 1024, flags, 0);
	_sc_card_add_rsa_alg(card, 1536, flags, 0);
	_sc_card_add_rsa_alg(card, 1792, flags, 0);
	_sc_card_add_rsa_alg(card, 2048, flags, 0);

	card->caps |= SC_CARD_CAP_APDU_EXT | SC_CARD_CAP_USE_FCI_AC;

	return SC_SUCCESS;
}
