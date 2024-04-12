call_allocate(struct rpc_task *task)
{
	unsigned int slack = task->tk_rqstp->rq_cred->cr_auth->au_cslack;
	struct rpc_rqst *req = task->tk_rqstp;
	struct rpc_xprt *xprt = task->tk_xprt;
	struct rpc_procinfo *proc = task->tk_msg.rpc_proc;

	dprint_status(task);

	task->tk_status = 0;
	task->tk_action = call_bind;

	if (req->rq_buffer)
		return;

	if (proc->p_proc != 0) {
		BUG_ON(proc->p_arglen == 0);
		if (proc->p_decode != NULL)
			BUG_ON(proc->p_replen == 0);
	}

	/*
	 * Calculate the size (in quads) of the RPC call
	 * and reply headers, and convert both values
	 * to byte sizes.
	 */
	req->rq_callsize = RPC_CALLHDRSIZE + (slack << 1) + proc->p_arglen;
	req->rq_callsize <<= 2;
	req->rq_rcvsize = RPC_REPHDRSIZE + slack + proc->p_replen;
	req->rq_rcvsize <<= 2;

	req->rq_buffer = xprt->ops->buf_alloc(task,
					req->rq_callsize + req->rq_rcvsize);
	if (req->rq_buffer != NULL)
		return;

	dprintk("RPC: %5u rpc_buffer allocation failed\n", task->tk_pid);

	if (RPC_IS_ASYNC(task) || !signalled()) {
		task->tk_action = call_allocate;
		rpc_delay(task, HZ>>4);
		return;
	}

	rpc_exit(task, -ERESTARTSYS);
}
