static ssize_t ib_ucm_listen(struct ib_ucm_file *file,
			     const char __user *inbuf,
			     int in_len, int out_len)
{
	struct ib_ucm_listen cmd;
	struct ib_ucm_context *ctx;
	int result;

	if (copy_from_user(&cmd, inbuf, sizeof(cmd)))
		return -EFAULT;

	ctx = ib_ucm_ctx_get(file, cmd.id);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	result = ucm_validate_listen(cmd.service_id, cmd.service_mask);
	if (result)
		goto out;

	result = ib_cm_listen(ctx->cm_id, cmd.service_id, cmd.service_mask);
out:
	ib_ucm_ctx_put(ctx);
	return result;
}
