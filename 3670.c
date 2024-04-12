static void srpt_cm_rep_error(struct ib_cm_id *cm_id)
{
	pr_info("Received IB REP error for cm_id %p.\n", cm_id);
	srpt_drain_channel(cm_id);
}
