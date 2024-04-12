    OVS_EXCLUDED(ofproto_mutex)
{
    enum ofperr error = ofproto_flow_mod_learn_refresh(ofm);
    struct rule *rule = ofm->temp_rule;

    /* Do we need to insert the rule? */
    if (!error && rule->state == RULE_INITIALIZED) {
        ovs_mutex_lock(&ofproto_mutex);
        ofm->version = rule->ofproto->tables_version + 1;
        error = ofproto_flow_mod_learn_start(ofm);
        if (!error) {
            ofproto_flow_mod_learn_finish(ofm, NULL);
        }
        ovs_mutex_unlock(&ofproto_mutex);
    }

    if (!keep_ref) {
        ofproto_rule_unref(rule);
        ofm->temp_rule = NULL;
    }
    return error;
}
