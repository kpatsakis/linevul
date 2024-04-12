void mon_st_callback(stonith_t *st, stonith_event_t *e)
{
    char *desc = g_strdup_printf(
        "Operation %s requested by %s for peer %s: %s (ref=%s)",
        e->operation, e->origin, e->target, pcmk_strerror(e->result), e->id); 

    if (snmp_target) {
        send_snmp_trap(e->target, NULL, e->operation, pcmk_ok, e->result, 0, desc);
    }
    if (crm_mail_to) {
        send_smtp_trap(e->target, NULL, e->operation, pcmk_ok, e->result, 0, desc);
    }
    if (external_agent) {
        send_custom_trap(e->target, NULL, e->operation, pcmk_ok, e->result, 0, desc);
    }
    g_free(desc);
}
