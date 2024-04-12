NICK_REC *nicklist_find(CHANNEL_REC *channel, const char *nick)
{
	g_return_val_if_fail(IS_CHANNEL(channel), NULL);
	g_return_val_if_fail(nick != NULL, NULL);

	return g_hash_table_lookup(channel->nicks, nick);
}
