static int nlmclnt_async_call(struct rpc_cred *cred, struct nlm_rqst *req, u32 proc, const struct rpc_call_ops *tk_ops)
{
	struct rpc_message msg = {
		.rpc_argp	= &req->a_args,
		.rpc_resp	= &req->a_res,
		.rpc_cred	= cred,
	};
	struct rpc_task *task;
	int err;

	task = __nlm_async_call(req, proc, &msg, tk_ops);
	if (IS_ERR(task))
		return PTR_ERR(task);
	err = rpc_wait_for_completion_task(task);
	rpc_put_task(task);
	return err;
}
