static ssize_t ib_ucm_send_rep(struct ib_ucm_file *file,
			       const char __user *inbuf,
			       int in_len, int out_len)
{
	struct ib_cm_rep_param param;
	struct ib_ucm_context *ctx;
	struct ib_ucm_rep cmd;
	int result;

	param.private_data = NULL;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	result = ib_ucm_alloc_data(&param.private_data, cmd.data, cmd.len);
	if (result)
		return result;

	param.qp_num              = cmd.qpn;
	param.starting_psn        = cmd.psn;
	param.private_data_len    = cmd.len;
	param.responder_resources = cmd.responder_resources;
	param.initiator_depth     = cmd.initiator_depth;
	param.failover_accepted   = cmd.failover_accepted;
	param.flow_control        = cmd.flow_control;
	param.rnr_retry_count     = cmd.rnr_retry_count;
	param.srq                 = cmd.srq;

	ctx = ib_ucm_ctx_get(file, cmd.id);
	if (!IS_ERR(ctx)) {
		ctx->uid = cmd.uid;
		result = ib_send_cm_rep(ctx->cm_id, &param);
		ib_ucm_ctx_put(ctx);
	} else
		result = PTR_ERR(ctx);

	kfree(param.private_data);
	return result;
}
