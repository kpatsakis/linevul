gpk_get_default_key(sc_card_t *card, struct sc_cardctl_default_key *data)
{
	if (data->method == SC_AC_PRO && data->key_ref == 1) {
		if (data->len < 16)
			return SC_ERROR_BUFFER_TOO_SMALL;
		memcpy(data->key_data, "TEST KEYTEST KEY", 16);
		data->len = 16;
		return 0;
	}
	return SC_ERROR_NO_DEFAULT_KEY;
}
