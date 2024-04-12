static int nfs4_lookup_root_sec(struct nfs_server *server, struct nfs_fh *fhandle,
				struct nfs_fsinfo *info, rpc_authflavor_t flavor)
{
	struct rpc_auth_create_args auth_args = {
		.pseudoflavor = flavor,
	};
	struct rpc_auth *auth;
	int ret;

	auth = rpcauth_create(&auth_args, server->client);
	if (IS_ERR(auth)) {
		ret = -EACCES;
		goto out;
	}
	ret = nfs4_lookup_root(server, fhandle, info);
out:
	return ret;
}
