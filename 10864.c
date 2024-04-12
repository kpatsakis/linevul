nfs_update_shareopts(sa_share_impl_t impl_share, const char *resource,
    const char *shareopts)
{
	char *shareopts_dup;
	boolean_t needs_reshare = B_FALSE;
	char *old_shareopts;

	FSINFO(impl_share, nfs_fstype)->active =
	    nfs_is_share_active(impl_share);

	old_shareopts = FSINFO(impl_share, nfs_fstype)->shareopts;

	if (strcmp(shareopts, "on") == 0)
		shareopts = "rw";

	if (FSINFO(impl_share, nfs_fstype)->active && old_shareopts != NULL &&
	    strcmp(old_shareopts, shareopts) != 0) {
		needs_reshare = B_TRUE;
		nfs_disable_share(impl_share);
	}

	shareopts_dup = strdup(shareopts);

	if (shareopts_dup == NULL)
		return (SA_NO_MEMORY);

	if (old_shareopts != NULL)
		free(old_shareopts);

	FSINFO(impl_share, nfs_fstype)->shareopts = shareopts_dup;

	if (needs_reshare)
		nfs_enable_share(impl_share);

	return (SA_OK);
}
