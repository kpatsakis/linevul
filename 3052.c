static int open_and_lock(char *path)
{
	int fd;
	struct flock lk;

	fd = open(path, O_RDWR|O_CREAT, S_IWUSR | S_IRUSR);
	if (fd < 0) {
		fprintf(stderr, "Failed to open %s: %s\n",
			path, strerror(errno));
		return(fd);
	}

	lk.l_type = F_WRLCK;
	lk.l_whence = SEEK_SET;
	lk.l_start = 0;
	lk.l_len = 0;
	if (fcntl(fd, F_SETLKW, &lk) < 0) {
		fprintf(stderr, "Failed to lock %s: %s\n",
			path, strerror(errno));
		close(fd);
		return -1;
	}

	return fd;
}
