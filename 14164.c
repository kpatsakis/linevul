static ssize_t ucma_listen(struct ucma_file *file, const char __user *inbuf,
			   int in_len, int out_len)
{
	struct rdma_ucm_listen cmd;
	struct ucma_context *ctx;
	int ret;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	ctx = ucma_get_ctx(file, cmd.id);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ctx->backlog = cmd.backlog > 0 && cmd.backlog < max_backlog ?
		       cmd.backlog : max_backlog;
	ret = rdma_listen(ctx->cm_id, ctx->backlog);
	ucma_put_ctx(ctx);
	return ret;
}
