nfs4_state_start(void)
{
	int ret;

	ret = set_callback_cred();
	if (ret)
		return ret;

	laundry_wq = alloc_workqueue("%s", WQ_UNBOUND, 0, "nfsd4");
	if (laundry_wq == NULL) {
		ret = -ENOMEM;
		goto out_cleanup_cred;
	}
	ret = nfsd4_create_callback_queue();
	if (ret)
		goto out_free_laundry;

	set_max_delegations();
	return 0;

out_free_laundry:
	destroy_workqueue(laundry_wq);
out_cleanup_cred:
	cleanup_callback_cred();
	return ret;
}
