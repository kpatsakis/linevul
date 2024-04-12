authentic_match_card(struct sc_card *card)
{
	struct sc_context *ctx = card->ctx;
	int i;

	sc_log_hex(ctx, "try to match card with ATR", card->atr.value, card->atr.len);
	i = _sc_match_atr(card, authentic_known_atrs, &card->type);
	if (i < 0)   {
		sc_log(ctx, "card not matched");
		return 0;
	}

	sc_log(ctx, "'%s' card matched", authentic_known_atrs[i].name);
	return 1;
}
