static ssize_t ucma_query_path(struct ucma_context *ctx,
			       void __user *response, int out_len)
{
	struct rdma_ucm_query_path_resp *resp;
	int i, ret = 0;

	if (out_len < sizeof(*resp))
		return -ENOSPC;

	resp = kzalloc(out_len, GFP_KERNEL);
	if (!resp)
		return -ENOMEM;

	resp->num_paths = ctx->cm_id->route.num_paths;
	for (i = 0, out_len -= sizeof(*resp);
	     i < resp->num_paths && out_len > sizeof(struct ib_path_rec_data);
	     i++, out_len -= sizeof(struct ib_path_rec_data)) {

		resp->path_data[i].flags = IB_PATH_GMP | IB_PATH_PRIMARY |
					   IB_PATH_BIDIRECTIONAL;
		ib_sa_pack_path(&ctx->cm_id->route.path_rec[i],
				&resp->path_data[i].path_rec);
	}

	if (copy_to_user(response, resp,
			 sizeof(*resp) + (i * sizeof(struct ib_path_rec_data))))
		ret = -EFAULT;

	kfree(resp);
	return ret;
}
