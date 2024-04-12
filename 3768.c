message_send_invite(const char *const roomjid, const char *const contact,
    const char *const reason)
{
    xmpp_ctx_t * const ctx = connection_get_ctx();
    xmpp_stanza_t *stanza;

    muc_member_type_t member_type = muc_member_type(roomjid);
    if (member_type == MUC_MEMBER_TYPE_PUBLIC) {
        log_debug("Sending direct invite to %s, for %s", contact, roomjid);
        char *password = muc_password(roomjid);
        stanza = stanza_create_invite(ctx, roomjid, contact, reason, password);
    } else {
        log_debug("Sending mediated invite to %s, for %s", contact, roomjid);
        stanza = stanza_create_mediated_invite(ctx, roomjid, contact, reason);
    }

    _send_message_stanza(stanza);
    xmpp_stanza_release(stanza);
}
