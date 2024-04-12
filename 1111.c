nfs_key_timeout_notify(struct file *filp, struct inode *inode)
{
	struct nfs_open_context *ctx = nfs_file_open_context(filp);
	struct rpc_auth *auth = NFS_SERVER(inode)->client->cl_auth;

	return rpcauth_key_timeout_notify(auth, ctx->cred);
}
