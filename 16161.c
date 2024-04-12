cib_ipc_accept(qb_ipcs_connection_t *c, uid_t uid, gid_t gid)
{
    cib_client_t *new_client = NULL;
#if ENABLE_ACL
    struct group *crm_grp = NULL;
#endif

    crm_trace("Connecting %p for uid=%d gid=%d pid=%d", c, uid, gid, crm_ipcs_client_pid(c));
    if (cib_shutdown_flag) {
        crm_info("Ignoring new client [%d] during shutdown", crm_ipcs_client_pid(c));
        return -EPERM;
    }

    new_client = calloc(1, sizeof(cib_client_t));
    new_client->ipc = c;

    CRM_CHECK(new_client->id == NULL, free(new_client->id));
    new_client->id = crm_generate_uuid();

#if ENABLE_ACL
    crm_grp = getgrnam(CRM_DAEMON_GROUP);
    if (crm_grp) {
        qb_ipcs_connection_auth_set(c, -1, crm_grp->gr_gid, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    }

    new_client->user = uid2username(uid);
#endif

    /* make sure we can find ourselves later for sync calls
     * redirected to the master instance
     */
    g_hash_table_insert(client_list, new_client->id, new_client);

    qb_ipcs_context_set(c, new_client);

    return 0;
}
