cib_ipc_destroy(qb_ipcs_connection_t *c) 
{
    cib_client_t *cib_client = qb_ipcs_context_get(c);

    CRM_ASSERT(cib_client != NULL);
    CRM_ASSERT(cib_client->id != NULL);

    /* In case we arrive here without a call to cib_ipc_close() */
    g_hash_table_remove(client_list, cib_client->id);

    crm_trace("Destroying %s (%p)", cib_client->name, c);
    free(cib_client->name);
    free(cib_client->callback_id);
    free(cib_client->id);
    free(cib_client->user);
    free(cib_client);
    crm_trace("Freed the cib client");

    if (cib_shutdown_flag) {
        cib_shutdown(0);
    }
}
