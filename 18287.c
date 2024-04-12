static int asepcos_get_default_key(sc_card_t *card,
	struct sc_cardctl_default_key *data)
{
	static const u8 asepcos_def_key[] = {0x41,0x53,0x45,0x43,0x41,0x52,0x44,0x2b};
	if (data->method != SC_AC_CHV && data->method != SC_AC_AUT)
		return SC_ERROR_NO_DEFAULT_KEY;
	if (data->key_data == NULL || data->len < sizeof(asepcos_def_key))
		return SC_ERROR_BUFFER_TOO_SMALL;
	memcpy(data->key_data, asepcos_def_key, sizeof(asepcos_def_key));
	data->len = sizeof(asepcos_def_key);
	return SC_SUCCESS;
}
