static int cac_match_card(sc_card_t *card)
{
	int r;
	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	/* Since we send an APDU, the card's logout function may be called...
	 * however it may be in dirty memory */
	card->ops->logout = NULL;

	r = cac_find_and_initialize(card, 0);
	return (r == SC_SUCCESS); /* never match */
}
