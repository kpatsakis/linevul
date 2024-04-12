static void rpc_release_resources_task(struct rpc_task *task)
{
	if (task->tk_rqstp)
		xprt_release(task);
	if (task->tk_msg.rpc_cred) {
		put_rpccred(task->tk_msg.rpc_cred);
		task->tk_msg.rpc_cred = NULL;
	}
	rpc_task_release_client(task);
}
