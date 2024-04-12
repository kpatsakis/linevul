cib_remote_register_notification(cib_t * cib, const char *callback, int enabled)
{
    xmlNode *notify_msg = create_xml_node(NULL, "cib_command");
    cib_remote_opaque_t *private = cib->variant_opaque;

    crm_xml_add(notify_msg, F_CIB_OPERATION, T_CIB_NOTIFY);
    crm_xml_add(notify_msg, F_CIB_NOTIFY_TYPE, callback);
    crm_xml_add_int(notify_msg, F_CIB_NOTIFY_ACTIVATE, enabled);
    crm_send_remote_msg(private->callback.session, notify_msg, private->callback.encrypted);
    free_xml(notify_msg);
    return pcmk_ok;
}
