int pin_rootfs(const char *rootfs)
{
	char absrootfs[MAXPATHLEN];
	char absrootfspin[MAXPATHLEN];
	struct stat s;
	int ret, fd;

	if (rootfs == NULL || strlen(rootfs) == 0)
		return -2;

	if (!realpath(rootfs, absrootfs))
		return -2;

	if (access(absrootfs, F_OK))
		return -1;

	if (stat(absrootfs, &s))
		return -1;

	if (!S_ISDIR(s.st_mode))
		return -2;

	ret = snprintf(absrootfspin, MAXPATHLEN, "%s/lxc.hold", absrootfs);
	if (ret >= MAXPATHLEN)
		return -1;

	fd = open(absrootfspin, O_CREAT | O_RDWR, S_IWUSR|S_IRUSR);
	if (fd < 0)
		return fd;
	(void)unlink(absrootfspin);
	return fd;
}
