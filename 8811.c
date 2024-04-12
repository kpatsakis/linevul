call_refreshresult(struct rpc_task *task)
{
	int status = task->tk_status;

	dprint_status(task);

	task->tk_status = 0;
	task->tk_action = call_refresh;
	switch (status) {
	case 0:
		if (rpcauth_uptodatecred(task))
			task->tk_action = call_allocate;
		return;
	case -ETIMEDOUT:
		rpc_delay(task, 3*HZ);
	case -EAGAIN:
		status = -EACCES;
		if (!task->tk_cred_retry)
			break;
		task->tk_cred_retry--;
		dprintk("RPC: %5u %s: retry refresh creds\n",
				task->tk_pid, __func__);
		return;
	}
	dprintk("RPC: %5u %s: refresh creds failed with error %d\n",
				task->tk_pid, __func__, status);
	rpc_exit(task, status);
}
