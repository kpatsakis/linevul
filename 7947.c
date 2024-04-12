static int nfs4_delay(struct rpc_clnt *clnt, long *timeout)
{
	int res = 0;

	might_sleep();

	freezable_schedule_timeout_killable_unsafe(
		nfs4_update_delay(timeout));
	if (fatal_signal_pending(current))
		res = -ERESTARTSYS;
	return res;
}
