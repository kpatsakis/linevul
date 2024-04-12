cib_shutdown(int nsig)
{
    struct qb_ipcs_stats srv_stats;
    if (cib_shutdown_flag == FALSE) {
        int disconnects = 0;
        qb_ipcs_connection_t *c = NULL;

        cib_shutdown_flag = TRUE;

        c = qb_ipcs_connection_first_get(ipcs_rw);
        while(c != NULL) {
            qb_ipcs_connection_t *last = c;
            c = qb_ipcs_connection_next_get(ipcs_rw, last);

            crm_debug("Disconnecting r/w client %p...", last);
            qb_ipcs_disconnect(last);
            qb_ipcs_connection_unref(last);
            disconnects++;
        }

        c = qb_ipcs_connection_first_get(ipcs_ro);
        while(c != NULL) {
            qb_ipcs_connection_t *last = c;
            c = qb_ipcs_connection_next_get(ipcs_ro, last);

            crm_debug("Disconnecting r/o client %p...", last);
            qb_ipcs_disconnect(last);
            qb_ipcs_connection_unref(last);
            disconnects++;
        }

        c = qb_ipcs_connection_first_get(ipcs_shm);
        while(c != NULL) {
            qb_ipcs_connection_t *last = c;
            c = qb_ipcs_connection_next_get(ipcs_shm, last);

            crm_debug("Disconnecting non-blocking r/w client %p...", last);
            qb_ipcs_disconnect(last);
            qb_ipcs_connection_unref(last);
            disconnects++;
        }

        disconnects += g_hash_table_size(client_list);

        crm_debug("Disconnecting %d remote clients", g_hash_table_size(client_list));
        g_hash_table_foreach(client_list, disconnect_remote_client, NULL);
        crm_info("Disconnected %d clients", disconnects);
    }

    qb_ipcs_stats_get(ipcs_rw, &srv_stats, QB_FALSE);
    
    if(g_hash_table_size(client_list) == 0) {
        crm_info("All clients disconnected (%d)", srv_stats.active_connections);
        initiate_exit();
        
    } else {
        crm_info("Waiting on %d clients to disconnect (%d)", g_hash_table_size(client_list), srv_stats.active_connections);
    }
}
