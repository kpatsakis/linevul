static void sig_server_setup_fill_reconn(IRC_SERVER_CONNECT_REC *conn,
					 IRC_SERVER_SETUP_REC *sserver)
{
        if (!IS_IRC_SERVER_CONNECT(conn) ||
	    !IS_IRC_SERVER_SETUP(sserver))
		return;

	if (sserver->cmd_queue_speed > 0)
		conn->cmd_queue_speed = sserver->cmd_queue_speed;
	if (sserver->max_cmds_at_once > 0)
		conn->max_cmds_at_once = sserver->max_cmds_at_once;
	if (sserver->max_query_chans > 0)
		conn->max_query_chans = sserver->max_query_chans;
}
