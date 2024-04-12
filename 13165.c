static int nfs4_proc_getattr(struct nfs_server *server, struct nfs_fh *fhandle,
				struct nfs_fattr *fattr, struct nfs4_label *label)
{
	struct nfs4_exception exception = { };
	int err;
	do {
		err = _nfs4_proc_getattr(server, fhandle, fattr, label);
		trace_nfs4_getattr(server, fhandle, fattr, err);
		err = nfs4_handle_exception(server, err,
				&exception);
	} while (exception.retry);
	return err;
}
