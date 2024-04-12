static int nfs41_proc_reclaim_complete(struct nfs_client *clp,
		struct rpc_cred *cred)
{
	struct nfs4_reclaim_complete_data *calldata;
	struct rpc_task *task;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RECLAIM_COMPLETE],
		.rpc_cred = cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = clp->cl_rpcclient,
		.rpc_message = &msg,
		.callback_ops = &nfs4_reclaim_complete_call_ops,
		.flags = RPC_TASK_ASYNC,
	};
	int status = -ENOMEM;

	dprintk("--> %s\n", __func__);
	calldata = kzalloc(sizeof(*calldata), GFP_NOFS);
	if (calldata == NULL)
		goto out;
	calldata->clp = clp;
	calldata->arg.one_fs = 0;

	nfs4_init_sequence(&calldata->arg.seq_args, &calldata->res.seq_res, 0);
	nfs4_set_sequence_privileged(&calldata->arg.seq_args);
	msg.rpc_argp = &calldata->arg;
	msg.rpc_resp = &calldata->res;
	task_setup_data.callback_data = calldata;
	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task)) {
		status = PTR_ERR(task);
		goto out;
	}
	status = nfs4_wait_for_completion_rpc_task(task);
	if (status == 0)
		status = task->tk_status;
	rpc_put_task(task);
	return 0;
out:
	dprintk("<-- %s status=%d\n", __func__, status);
	return status;
}
