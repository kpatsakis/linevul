send_peer_reply(xmlNode * msg, xmlNode * result_diff, const char *originator, gboolean broadcast)
{
    CRM_ASSERT(msg != NULL);

    if (broadcast) {
        /* this (successful) call modified the CIB _and_ the
         * change needs to be broadcast...
         *   send via HA to other nodes
         */
        int diff_add_updates = 0;
        int diff_add_epoch = 0;
        int diff_add_admin_epoch = 0;

        int diff_del_updates = 0;
        int diff_del_epoch = 0;
        int diff_del_admin_epoch = 0;

        const char *digest = NULL;

        digest = crm_element_value(result_diff, XML_ATTR_DIGEST);
        cib_diff_version_details(result_diff,
                                 &diff_add_admin_epoch, &diff_add_epoch, &diff_add_updates,
                                 &diff_del_admin_epoch, &diff_del_epoch, &diff_del_updates);

        crm_trace("Sending update diff %d.%d.%d -> %d.%d.%d %s",
                    diff_del_admin_epoch, diff_del_epoch, diff_del_updates,
                  diff_add_admin_epoch, diff_add_epoch, diff_add_updates, digest);

        crm_xml_add(msg, F_CIB_ISREPLY, originator);
        crm_xml_add(msg, F_CIB_GLOBAL_UPDATE, XML_BOOLEAN_TRUE);
        crm_xml_add(msg, F_CIB_OPERATION, CIB_OP_APPLY_DIFF);

        CRM_ASSERT(digest != NULL);

        add_message_xml(msg, F_CIB_UPDATE_DIFF, result_diff);
        crm_log_xml_trace(msg, "copy");
        return send_cluster_message(NULL, crm_msg_cib, msg, TRUE);

    } else if (originator != NULL) {
        /* send reply via HA to originating node */
        crm_trace("Sending request result to originator only");
        crm_xml_add(msg, F_CIB_ISREPLY, originator);
        return send_cluster_message(crm_get_peer(0, originator), crm_msg_cib, msg, FALSE);
    }

    return FALSE;
}
