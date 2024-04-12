static char *server_create_address_tag(const char *address)
{
	const char *start, *end;

	g_return_val_if_fail(address != NULL, NULL);

	/* try to generate a reasonable server tag */
	if (strchr(address, '.') == NULL) {
		start = end = NULL;
	} else if (g_ascii_strncasecmp(address, "irc", 3) == 0 ||
	    g_ascii_strncasecmp(address, "chat", 4) == 0) {
		/* irc-2.cs.hut.fi -> hut, chat.bt.net -> bt */
		end = strrchr(address, '.');
		start = end-1;
		while (start > address && *start != '.') start--;
	} else {
		/* efnet.cs.hut.fi -> efnet */
		end = strchr(address, '.');
		start = end;
	}

	if (start == end) start = address; else start++;
	if (end == NULL) end = address + strlen(address);

	return g_strndup(start, (int) (end-start));
}
