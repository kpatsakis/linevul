static void grace_ender(struct work_struct *grace)
{
	struct delayed_work *dwork = to_delayed_work(grace);
	struct lockd_net *ln = container_of(dwork, struct lockd_net,
					    grace_period_end);

	locks_end_grace(&ln->lockd_manager);
}
