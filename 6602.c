static void disconnect_servers(GSList *servers, int chat_type)
{
	GSList *tmp, *next;

	for (tmp = servers; tmp != NULL; tmp = next) {
		SERVER_REC *rec = tmp->data;

                next = tmp->next;
                if (rec->chat_type == chat_type)
			server_disconnect(rec);
	}
}
