static struct llc_sap_state_trans *llc_find_sap_trans(struct llc_sap *sap,
						      struct sk_buff *skb)
{
	int i = 0;
	struct llc_sap_state_trans *rc = NULL;
	struct llc_sap_state_trans **next_trans;
	struct llc_sap_state *curr_state = &llc_sap_state_table[sap->state - 1];
	/*
	 * Search thru events for this state until list exhausted or until
	 * its obvious the event is not valid for the current state
	 */
	for (next_trans = curr_state->transitions; next_trans[i]->ev; i++)
		if (!next_trans[i]->ev(sap, skb)) {
			rc = next_trans[i]; /* got event match; return it */
			break;
		}
	return rc;
}
