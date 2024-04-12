static void nfs4_put_deleg_lease(struct nfs4_file *fp)
{
	struct file *filp = NULL;

	spin_lock(&fp->fi_lock);
	if (fp->fi_deleg_file && --fp->fi_delegees == 0)
		swap(filp, fp->fi_deleg_file);
	spin_unlock(&fp->fi_lock);

	if (filp) {
		vfs_setlease(filp, F_UNLCK, NULL, (void **)&fp);
		fput(filp);
	}
}
