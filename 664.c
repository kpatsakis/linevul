static void mk_request_premature_close(int http_status, struct client_session *cs)
{
    struct session_request *sr;
    struct mk_list *sr_list = &cs->request_list;
    struct mk_list *host_list = &config->hosts;

    /*
     * If the connection is too premature, we need to allocate a temporal session_request
     * to do not break the plugins stages
     */
    if (mk_list_is_empty(sr_list) == 0) {
        sr = &cs->sr_fixed;
        memset(sr, 0, sizeof(struct session_request));
        mk_request_init(sr);
        mk_list_add(&sr->_head, &cs->request_list);
    }
    else {
        sr = mk_list_entry_first(sr_list, struct session_request, _head);
    }

    /* Raise error */
    if (http_status > 0) {
        if (!sr->host_conf) {
            sr->host_conf = mk_list_entry_first(host_list, struct host, _head);
        }
        mk_request_error(http_status, cs, sr);

        /* STAGE_40, request has ended */
        mk_plugin_stage_run(MK_PLUGIN_STAGE_40, cs->socket,
                            NULL, cs, sr);
    }

    /* STAGE_50, connection closed  and remove client_session*/
    mk_plugin_stage_run(MK_PLUGIN_STAGE_50, cs->socket, NULL, NULL, NULL);
    mk_session_remove(cs->socket);
}
