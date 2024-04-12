void server_connect_unref(SERVER_CONNECT_REC *conn)
{
	g_return_if_fail(IS_SERVER_CONNECT(conn));

	if (--conn->refcount > 0)
		return;
	if (conn->refcount < 0) {
		g_warning("Connection '%s' refcount = %d",
			  conn->tag, conn->refcount);
	}

        CHAT_PROTOCOL(conn)->destroy_server_connect(conn);

	if (conn->connect_handle != NULL)
		net_disconnect(conn->connect_handle);

	g_free_not_null(conn->proxy);
	g_free_not_null(conn->proxy_string);
	g_free_not_null(conn->proxy_string_after);
	g_free_not_null(conn->proxy_password);

	g_free_not_null(conn->tag);
	g_free_not_null(conn->address);
	g_free_not_null(conn->chatnet);

	g_free_not_null(conn->own_ip4);
	g_free_not_null(conn->own_ip6);

        g_free_not_null(conn->password);
        g_free_not_null(conn->nick);
        g_free_not_null(conn->username);
	g_free_not_null(conn->realname);

	g_free_not_null(conn->ssl_cert);
	g_free_not_null(conn->ssl_pkey);
	g_free_not_null(conn->ssl_cafile);
	g_free_not_null(conn->ssl_capath);

	g_free_not_null(conn->channels);
        g_free_not_null(conn->away_reason);

        conn->type = 0;
	g_free(conn);
}
