network_connect_gnutls_handshake_timer_cb (void *arg_hook_connect,
                                           int remaining_calls)
{
    struct t_hook *hook_connect;
    
    /* make C compiler happy */
    (void) remaining_calls;
    
    hook_connect = (struct t_hook *)arg_hook_connect;
    
    HOOK_CONNECT(hook_connect, handshake_hook_timer) = NULL;
    
    (void) (HOOK_CONNECT(hook_connect, callback))
            (hook_connect->callback_data,
             WEECHAT_HOOK_CONNECT_GNUTLS_HANDSHAKE_ERROR,
             GNUTLS_E_EXPIRED,
             gnutls_strerror (GNUTLS_E_EXPIRED),
             HOOK_CONNECT(hook_connect, handshake_ip_address));
    unhook (hook_connect);
    
    return WEECHAT_RC_OK;
}
