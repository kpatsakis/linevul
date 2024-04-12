GSList *nicklist_get_same(SERVER_REC *server, const char *nick)
{
	GSList *tmp;
	GSList *list = NULL;

	g_return_val_if_fail(IS_SERVER(server), NULL);

	for (tmp = server->channels; tmp != NULL; tmp = tmp->next) {
		NICK_REC *nick_rec;
		CHANNEL_REC *channel = tmp->data;

		for (nick_rec = g_hash_table_lookup(channel->nicks, nick);
		     nick_rec != NULL;
		     nick_rec = nick_rec->next) {
			list = g_slist_append(list, channel);
			list = g_slist_append(list, nick_rec);
		}
	}

	return list;
}
