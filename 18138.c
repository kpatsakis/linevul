irc_server_recv_cb (void *data, int fd)
{
    struct t_irc_server *server;
    static char buffer[4096 + 2];
    int num_read;
    
    /* make C compiler happy */
    (void) fd;
    
    server = (struct t_irc_server *)data;
    
    if (!server)
        return WEECHAT_RC_ERROR;
    
#ifdef HAVE_GNUTLS
    if (server->ssl_connected)
        num_read = gnutls_record_recv (server->gnutls_sess, buffer,
                                       sizeof (buffer) - 2);
    else
#endif
        num_read = recv (server->sock, buffer, sizeof (buffer) - 2, 0);
    
    if (num_read > 0)
    {
        buffer[num_read] = '\0';
        irc_server_msgq_add_buffer (server, buffer);
        irc_server_msgq_flush ();
    }
    else
    {
#ifdef HAVE_GNUTLS
        if (server->ssl_connected)
        {
            if ((num_read == 0)
                || ((num_read != GNUTLS_E_AGAIN) && (num_read != GNUTLS_E_INTERRUPTED)))
            {
                weechat_printf (server->buffer,
                                _("%s%s: reading data on socket: error %d %s"),
                                weechat_prefix ("error"), IRC_PLUGIN_NAME,
                                num_read,
                                (num_read == 0) ? _("(connection closed by peer)") :
                                gnutls_strerror (num_read));
                weechat_printf (server->buffer,
                                _("%s: disconnecting from server..."),
                                IRC_PLUGIN_NAME);
                irc_server_disconnect (server, !server->is_connected, 1);
            }
        }
        else
#endif
        {
            if ((num_read == 0)
                || ((errno != EAGAIN) && (errno != EWOULDBLOCK)))
            {
                weechat_printf (server->buffer,
                                _("%s%s: reading data on socket: error %d %s"),
                                weechat_prefix ("error"), IRC_PLUGIN_NAME,
                                errno,
                                (num_read == 0) ? _("(connection closed by peer)") :
                                strerror (errno));
                weechat_printf (server->buffer,
                                _("%s: disconnecting from server..."),
                                IRC_PLUGIN_NAME);
                irc_server_disconnect (server, !server->is_connected, 1);
            }
        }
    }
    
    return WEECHAT_RC_OK;
}
