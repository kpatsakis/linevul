static int nfs4_proc_remove(struct inode *dir, struct qstr *name)
{
	struct nfs4_exception exception = { };
	int err;
	do {
		err = _nfs4_proc_remove(dir, name);
		trace_nfs4_remove(dir, name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	} while (exception.retry);
	return err;
}
