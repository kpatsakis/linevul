rpc_task_set_rpc_message(struct rpc_task *task, const struct rpc_message *msg)
{
	if (msg != NULL) {
		task->tk_msg.rpc_proc = msg->rpc_proc;
		task->tk_msg.rpc_argp = msg->rpc_argp;
		task->tk_msg.rpc_resp = msg->rpc_resp;
		if (msg->rpc_cred != NULL)
			task->tk_msg.rpc_cred = get_rpccred(msg->rpc_cred);
	}
}
