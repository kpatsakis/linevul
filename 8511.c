static int sig_check_netjoins(void)
{
	GSList *tmp, *next;
	int diff;
	time_t now;

	now = time(NULL);
	/* first print all netjoins which haven't had any new joins
	 * for NETJOIN_WAIT_TIME; this may cause them to be removed
	 * (all users who rejoined, rejoined all channels) */
	for (tmp = joinservers; tmp != NULL; tmp = next) {
		NETJOIN_SERVER_REC *server = tmp->data;

		next = tmp->next;
		diff = now-server->last_netjoin;
		if (diff <= NETJOIN_WAIT_TIME) {
			/* wait for more JOINs */
			continue;
		}

                if (server->netjoins != NULL)
			print_netjoins(server, NULL);
	}

	/* now remove all netjoins which haven't had any new joins
	 * for NETJOIN_MAX_WAIT (user rejoined some but not all channels
	 * after split) */
	for (tmp = joinservers; tmp != NULL; tmp = next) {
		NETJOIN_SERVER_REC *server = tmp->data;

		next = tmp->next;
		diff = now-server->last_netjoin;
		if (diff >= NETJOIN_MAX_WAIT) {
			/* waited long enough, forget about the rest */
                        netjoin_server_remove(server);
		}
	}

	if (joinservers == NULL) {
		g_source_remove(join_tag);
		signal_remove("print starting", (SIGNAL_FUNC) sig_print_starting);
                join_tag = -1;
	}
	return 1;
}
