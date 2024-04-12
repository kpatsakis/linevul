irc_server_login (struct t_irc_server *server)
{
    const char *password, *username, *realname;
    
    password = IRC_SERVER_OPTION_STRING(server, IRC_SERVER_OPTION_PASSWORD);
    username = IRC_SERVER_OPTION_STRING(server, IRC_SERVER_OPTION_USERNAME);
    realname = IRC_SERVER_OPTION_STRING(server, IRC_SERVER_OPTION_REALNAME);
    
    if (password && password[0])
        irc_server_sendf (server, 0, NULL, "PASS %s", password);
    
    if (!server->nick)
    {
        irc_server_set_nick (server,
                             (server->nicks_array) ?
                             server->nicks_array[0] : "weechat");
        server->nick_first_tried = 0;
    }
    else
        server->nick_first_tried = irc_server_get_nick_index (server);
    
    if (irc_server_sasl_enabled (server))
    {
        irc_server_sendf (server, 0, NULL, "CAP LS");
    }
    
    irc_server_sendf (server, 0, NULL,
                      "NICK %s\n"
                      "USER %s %s %s :%s",
                      server->nick,
                      (username && username[0]) ? username : "weechat",
                      (username && username[0]) ? username : "weechat",
                      server->current_address,
                      (realname && realname[0]) ? realname : ((username && username[0]) ? username : "weechat"));
    
    if (server->hook_timer_connection)
        weechat_unhook (server->hook_timer_connection);
    server->hook_timer_connection = weechat_hook_timer (
        IRC_SERVER_OPTION_INTEGER (server, IRC_SERVER_OPTION_CONNECTION_TIMEOUT) * 1000,
        0, 1,
        &irc_server_timer_connection_cb,
        server);
}
