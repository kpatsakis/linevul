static int fsmSymlink(const char *opath, const char *path)
{
    int rc = symlink(opath, path);

    if (_fsm_debug) {
	rpmlog(RPMLOG_DEBUG, " %8s (%s, %s) %s\n", __func__,
	       opath, path, (rc < 0 ? strerror(errno) : ""));
    }

    if (rc < 0)
	rc = RPMERR_SYMLINK_FAILED;
    return rc;
}
