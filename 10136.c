setlogfile(argv)
    char **argv;
{
    int fd, err;
    uid_t euid;

    euid = geteuid();
    if (!privileged_option && seteuid(getuid()) == -1) {
	option_error("unable to drop permissions to open %s: %m", *argv);
	return 0;
    }
    fd = open(*argv, O_WRONLY | O_APPEND | O_CREAT | O_EXCL, 0644);
    if (fd < 0 && errno == EEXIST)
	fd = open(*argv, O_WRONLY | O_APPEND);
    err = errno;
    if (!privileged_option && seteuid(euid) == -1)
	fatal("unable to regain privileges: %m");
    if (fd < 0) {
	errno = err;
	option_error("Can't open log file %s: %m", *argv);
	return 0;
    }
    strlcpy(logfile_name, *argv, sizeof(logfile_name));
    if (logfile_fd >= 0)
	close(logfile_fd);
    logfile_fd = fd;
    log_to_fd = fd;
    log_default = 0;
    return 1;
}
