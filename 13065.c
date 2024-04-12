static int lockd_start_svc(struct svc_serv *serv)
{
	int error;

	if (nlmsvc_rqst)
		return 0;

	/*
	 * Create the kernel thread and wait for it to start.
	 */
	nlmsvc_rqst = svc_prepare_thread(serv, &serv->sv_pools[0], NUMA_NO_NODE);
	if (IS_ERR(nlmsvc_rqst)) {
		error = PTR_ERR(nlmsvc_rqst);
		printk(KERN_WARNING
			"lockd_up: svc_rqst allocation failed, error=%d\n",
			error);
		goto out_rqst;
	}

	svc_sock_update_bufs(serv);
	serv->sv_maxconn = nlm_max_connections;

	nlmsvc_task = kthread_create(lockd, nlmsvc_rqst, "%s", serv->sv_name);
	if (IS_ERR(nlmsvc_task)) {
		error = PTR_ERR(nlmsvc_task);
		printk(KERN_WARNING
			"lockd_up: kthread_run failed, error=%d\n", error);
		goto out_task;
	}
	nlmsvc_rqst->rq_task = nlmsvc_task;
	wake_up_process(nlmsvc_task);

	dprintk("lockd_up: service started\n");
	return 0;

out_task:
	lockd_svc_exit_thread();
	nlmsvc_task = NULL;
out_rqst:
	nlmsvc_rqst = NULL;
	return error;
}
