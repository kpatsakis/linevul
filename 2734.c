    OVS_EXCLUDED(ofproto_mutex)
{
    /* This skips the ofmonitor and flow-removed notifications because the
     * switch is being deleted and any OpenFlow channels have been or soon will
     * be killed. */
    ovs_mutex_lock(&ofproto_mutex);

    if (rule->state == RULE_INSERTED) {
        /* Make sure there is no postponed removal of the rule. */
        ovs_assert(cls_rule_visible_in_version(&rule->cr, OVS_VERSION_MAX));

        if (!classifier_remove(&rule->ofproto->tables[rule->table_id].cls,
                               &rule->cr)) {
            OVS_NOT_REACHED();
        }
        ofproto_rule_remove__(rule->ofproto, rule);
        if (ofproto->ofproto_class->rule_delete) {
            ofproto->ofproto_class->rule_delete(rule);
        }

        /* This may not be the last reference to the rule. */
        ofproto_rule_unref(rule);
    }
    ovs_mutex_unlock(&ofproto_mutex);
}
