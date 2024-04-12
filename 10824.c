static int fsmBackup(rpmfi fi, rpmFileAction action)
{
    int rc = 0;
    const char *suffix = NULL;

    if (!(rpmfiFFlags(fi) & RPMFILE_GHOST)) {
	switch (action) {
	case FA_SAVE:
	    suffix = SUFFIX_RPMSAVE;
	    break;
	case FA_BACKUP:
	    suffix = SUFFIX_RPMORIG;
	    break;
	default:
	    break;
	}
    }

    if (suffix) {
	char * opath = fsmFsPath(fi, NULL);
	char * path = fsmFsPath(fi, suffix);
	rc = fsmRename(opath, path);
	if (!rc) {
	    rpmlog(RPMLOG_WARNING, _("%s saved as %s\n"), opath, path);
	}
	free(path);
	free(opath);
    }
    return rc;
}
