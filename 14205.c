auth_check_sw(struct sc_card *card, unsigned int sw1, unsigned int sw2)
{
	int ii;

	for (ii=0; auth_warnings[ii].SWs; ii++)   {
		if (auth_warnings[ii].SWs == ((sw1 << 8) | sw2))   {
			sc_log(card->ctx, "%s", auth_warnings[ii].errorstr);
			return auth_warnings[ii].errorno;
		}
	}

	return iso_ops->check_sw(card, sw1, sw2);
}
